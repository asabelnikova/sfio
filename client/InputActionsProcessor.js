
let MousePosition;
let PlayerId;

export function setPlayerId(id) {
  PlayerId = id;
}
export function setMousePosition(pos) {
  MousePosition = pos;
}
export function processPlayerInputs(playerId, inputs) {
  let actions = inputs.map(mapInputToAction(playerId));
  return actions;
}

const ActionMap = new Map([[32, 'trust'], ['mouse_left', 'shoot']]);


function mapInputToAction(id) {
  return function(input) {
    return {
      id,
      action: ActionMap[input.code], 
      to: input.mouse.map(x => x), 
      dt: input.id,
      startedOn: input.startedOn
    }
  }
}
