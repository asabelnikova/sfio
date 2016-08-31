import THREE from 'three';

let Scene = null;
const PlayerIdMeshMap = new Map;

export function syncronize(players){
  //console.log(players);
  let touchedIds = []
  players.forEach(player=>{
    console.log(player);
    let id = player.id;
    touchedIds.push(id);
    if(!(id in PlayerIdMeshMap)) {
      let mesh = createMesh(player);
      PlayerIdMeshMap.set(id,  mesh);
      Scene.add(mesh);
    }
    let actions = player.actions;
    let initial = player.initial;
    let current = calculatePosition(initial, actions);
    applyNewStateToMesh(id, current);
  });

  let deleted = new Set(PlayerIdMeshMap.keys());
  
  touchedIds.forEach(item=>{
    deleted.delete(item);
  });
  deleted.forEach(item=>{
    Scene.remove(PlayerIdMeshMap.get(item));
    PlayerIdMeshMap.delete(item)
  })
}

export function setScene(s){ Scene = s; }

function createMesh(player){
  let material = new THREE.MeshBasicMaterial({color: 0xffee33});
  let geometry = new THREE.CircleBufferGeometry(0.1,36);
  return new THREE.Mesh(geometry, material);
}


function calculatePosition(initial, actions){
  //console.warn("Don't expect something to happen");
  return {
    position: [0,0],
    velocity: [0,0]
  }
}

function applyNewStateToMesh(id, currentState){
  //console.warn('applyNewStateToMesh does nothing');
}

