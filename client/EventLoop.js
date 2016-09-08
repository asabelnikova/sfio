import THREE from 'three';
let Camera = null;
const KeysState = new Map;
let Keyboard = [];
let zeroServerTime = 0;
let CurrentMousePosition;
let mousePositionCallbacs = [];

document.addEventListener('keydown', keyDown());
document.addEventListener('keyup', keyUp());
document.addEventListener('mousedown', keyDown(mouseCode));
document.addEventListener('mouseup', keyUp(mouseCode));
document.addEventListener('mousemove', function(evt) {
  let worldPosition = getWorldMousePosition([evt.clientX, evt.clientY]);
  CurrentMousePosition = worldPosition;
  mousePositionCallbacs.map(fn => fn(worldPosition))
});

function frame(draw, keys) {
  let now = Date.now() - zeroServerTime;
  collect(now);
  let commands = Keyboard;
  Keyboard = [];
  keys(commands);
  draw(now);
  requestAnimationFrame(() => frame(draw, keys));
}

function mouseCode(evt) {
  if (evt.button == 0) return 'mouse_left';
  if (evt.button == 1) return 'mouse_middle';
  if (evt.button == 2) return 'mouse_right';
}
export default function(renderFunction, keyTimesFunction) {
  frame(renderFunction, keyTimesFunction);
};
export function setZeroTime(t) {
  zeroServerTime = t;
}
export function setCamera(c) {
  Camera = c;
}
export function onMouseCallback(fn) {
  mousePositionCallbacs.push(fn);
}
let Raycaster = new THREE.Raycaster();
function getWorldMousePosition(p) {
  let normalized = new THREE.Vector3();
  let planeNormal = new THREE.Vector3();
  let planePoint = new THREE.Vector3();
  planeNormal.set(0, 0, 1.0);
  planePoint.set(0, 0, 0);
  planePoint.sub(Camera.position);
  let pdot = planeNormal.dot(planePoint);
  if (!Camera) return normalized;
  normalized.x = (p[0] / window.innerWidth) * 2 - 1.0;
  normalized.y = -(p[1] / window.innerHeight) * 2 + 1.0;
  normalized.z = 0.0;
  Raycaster.setFromCamera(normalized, Camera);
  let ray = Raycaster.ray;
  let eyeDot = ray.direction.dot(new THREE.Vector3(0, 0, 1.0));
  let d = pdot / eyeDot;
  ray.direction.multiplyScalar(d);
  let pos = ray.origin.add(ray.direction);
  return pos;
}

function keyDown(evtFunc = (e) => e.keyCode) {
  return function(evt) {
    if (evt.repeat) return;
    let code = evtFunc(evt);
    KeysState.set(code, Date.now() - zeroServerTime);
  }
}

function keyUp(evtFunc = (e) => e.keyCode) {
  return function(evt) {
    let code = evtFunc(evt);
    let t = Date.now() - zeroServerTime;
    let ft = KeysState.get(code);
    if (!ft) return;
    KeysState.delete(code);
    Keyboard.push({
      code,
      dt: (t - ft) / 1000.0,
      startedOn: ft,
      mouse: CurrentMousePosition.clone()
    });
  }
}

function collect(t) {
  for (let [k, ft] of KeysState.entries()) {
    Keyboard.push({
      code: k,
      dt: (t - ft) / 1000.0,
      startedOn: ft,
      mouse: CurrentMousePosition.clone()
    });
    KeysState.set(k, t);
  }
}
