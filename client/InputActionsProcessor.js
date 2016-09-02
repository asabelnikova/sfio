

const ActionMap = new Map([[32, 'thrust'], ['mouse_left', 'shoot']]);
let MousePosition;
let PlayerId;

export function setPlayerId(id) {
  PlayerId = id;
}
export function setMousePosition(pos) {
  MousePosition = pos;
}
export function processPlayerInputs(playerId, inputs) {
  let actions = inputs.filter(definedActions).map(mapInputToAction(playerId));
  return actions;
}

function definedActions(a){
  return ActionMap.has(a.code);
}



function mapInputToAction(id) {
  return function(input) {
    return {
      id,
      action: ActionMap.get(input.code), 
      onPoint: input.mouse,
      dt: input.dt,
      startedOn: input.startedOn
    }
  }
}
