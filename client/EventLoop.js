

const KeysState = {};
let Keyboard = [];
let zeroServerTime = 0;
let CurrentMousePosition;

document.addEventListener('keydown', keyDown());
document.addEventListener('keyup', keyUp());
document.addEventListener('mousedown', keyDown(mouseCode));
document.addEventListener('mouseup', keyUp(mouseCode));

function frame(draw, keys) {
  collect();
  let commands = Keyboard;
  Keyboard = [];
  keys(commands);
  draw();
  requestAnimationFrame(() => frame(draw, keys));
}

function mouseCode(evt){
  if(evt.button == 0) return 'mouse_left';
  if(evt.button == 1) return 'mouse_middle';
  if(evt.button == 2) return 'mouse_right';
}
export default function(renderFunction, keyTimesFunction) {
  frame(renderFunction, keyTimesFunction);
};
export function setZeroTime(t){
  zeroServerTime = t;
}
export function setCurrentMousePosition(p){
  CurrentMousePosition = p;
}

//function mouseDown(evt){
  //console.log(evt.button);
//}
//function mouseUp(){
//}
function keyDown(evtFunc = (e)=>e.keyCode) {
  return function(evt){
    if (evt.repeat) return;
    let code = evtFunc(evt); 
    KeysState[code] = Date.now();
  }
}

function keyUp(evtFunc =  (e)=>e.keyCode) {
  return  function (evt){
    let code = evtFunc(evt);
    let t = Date.now();
    let ft = KeysState[code];
    delete KeysState[code];
    Keyboard.push({
      code, 
      dt: t - ft, 
      startedOn: ft - zeroServerTime, 
      mouse:CurrentMousePosition.map(x=>x)
    });
  }
}

function collect() {
  let t = Date.now();
  for (let k in KeysState) {
    let ft = KeysState[k];
    Keyboard.push({
      code: k, 
      dt: t - ft, 
      startedOn: ft - zeroServerTime,
      mouse:CurrentMousePosition.map(x=>x)
    });

    KeysState[k] = t;
  }
}
