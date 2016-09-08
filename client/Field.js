import THREE from 'three';

let Scene = null;
const PlayerIdMeshMap = new Map;

export function syncronize(players, now) {
  let touchedIds = [];
  players.forEach((player, id) => {
    touchedIds.push(id);
    if (!PlayerIdMeshMap.has(id)) {
      let mesh = createMesh(player);
      PlayerIdMeshMap.set(id, mesh);
      Scene.add(mesh);
    }
    let current = applyActions(player, now);
    if (!current) return;
    updateWithVelocities(current, now);
    applyNewStateToMesh(id, current);
  });

  let deleted = new Set(PlayerIdMeshMap.keys());

  touchedIds.forEach(item => { deleted.delete(item); });
  deleted.forEach(item => {
    Scene.remove(PlayerIdMeshMap.get(item));
    PlayerIdMeshMap.delete(item)
  })
}

export function setScene(s) {
  Scene = s;
}

function updateWithVelocities(state, now) {
  for (let key in state) {
    let p = state[key];
    if (now > p.calculatedAt) {
      let dt = (now - p.calculatedAt) / 1000;
      if (p.scalar) {
        p.scalar.v += p.scalar.dv * dt;
      }
      if (p.vec2) {
        p.vec2.v.x += p.vec2.dv.x * dt;
        p.vec2.v.y += p.vec2.dv.y * dt;
      }
    }
  }
}

function createMesh(player) {
  let material = new THREE.MeshBasicMaterial({color: 0xffee33});
  let geometry = new THREE.CircleBufferGeometry(0.1, 36);
  return new THREE.Mesh(geometry, material);
}

let ActionProcessors =
    {
      thrust: function(initial, action) {
        let pos = initial.position;
        let mass = initial.mass ? initial.mass.scalar.v : 100;
        let thrust = initial.thrust ? initial.thrust.scalar.v : 10;
        let currentPos = new THREE.Vector3(pos.vec2.v.x, pos.vec2.v.y, 0);
        let dtLinear = (action.startedOn - pos.calculatedAt) / 1000;
        let dt = action.dt;
        let dv = {
          x: pos.vec2.dv.x * dtLinear,
          y: pos.vec2.dv.y * dtLinear,
          z: 0
        };
        let dva = {x: pos.vec2.dv.x * dt, y: pos.vec2.dv.y * dt, z: 0};
        let a = action.onPoint.clone()
                    .sub(currentPos)
                    .normalize()
                    .multiplyScalar(thrust / mass);
        pos.calculatedAt = action.startedOn + action.dt * 1000.0;
        let at = a.clone().multiplyScalar(action.dt);
        let at2 = a.clone().multiplyScalar(action.dt * action.dt * 0.5);
        pos.vec2.dv.x += at.x;
        pos.vec2.dv.y += at.y;
        pos.vec2.v.x += dv.x + at2.x + dva.x;
        pos.vec2.v.y += dv.y + at2.y + dva.y;
        console.log("dvelocity", Math.hypot(at.x, at.y));
      }
    }

function applyActions(player) {
  if (!player.has('parameters')) return;
  let initial = player.get('parameters').toJS();
  if (!player.has('actions')) return initial;

  player.get('actions').forEach(action => {
    let a = action.action;
    if (ActionProcessors[a]) ActionProcessors[a](initial, action);
  });
  return initial;
}


function applyNewStateToMesh(id, currentState) {
  if (!currentState) return console.warn('undefined state');
  let pos = currentState.position.vec2.v;
  let mesh = PlayerIdMeshMap.get(id);
  mesh.position.x = pos.x;
  mesh.position.y = pos.y;
}
