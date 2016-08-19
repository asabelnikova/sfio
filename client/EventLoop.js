

const KeysState = {};

let Keyboard = [];
document.addEventListener('keydown', keyDown);

document.addEventListener('keyup', keyUp);


function frame(draw, keys) {
  collect();
  let commands = Keyboard;
  Keyboard = [];
  keys(commands);
  requestAnimationFrame(() => frame(draw, keys));
}

export default function(renderFunction, keyTimesFunction) {
  frame(renderFunction, keyTimesFunction);
};

function keyDown(evt) {
  if (evt.repeat) return;
  let code = evt.keyCode;
  KeysState[code] = Date.now();
}

function keyUp(evt) {
  let code = evt.keyCode;
  let t = Date.now();
  let ft = KeysState[code];
  delete KeysState[code];
  Keyboard.push({code, dt: t - ft});
}

function collect() {
  let t = Date.now();
  for (let k in KeysState) {
    let ft = KeysState[k];
    Keyboard.push({code: k, dt: t - ft});
    KeysState[k] = t;
  }
}
