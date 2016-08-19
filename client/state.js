'use strict';

const state = {
  id: null
};

export default function get() {
  return {
    setField(f) { state.field = f; }
    , setZeroTimePoint(time) { state.zeroTimePoint = time; }
    , setName(n) { state.name = n; }
    , setId(id) { state.id = id; }
    , addPlayerCommand(c) { state.field.players.commands.push(c); }
    , isInGame() {
      console.log(state.id === null);
      return state.id !== null;
    }
  }
}
