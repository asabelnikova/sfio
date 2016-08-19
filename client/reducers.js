import {combineReducers} from 'redux';
import {List, Map, fromJS} from 'immutable';
import {PLAYER_STATE_RECV, HANDSHAKE_DONE} from './actions.js';

const defaultState = {
  id: null,
  player: {energy: 0, isAlive: false}
};

function state(state = fromJS(defaultState), action) {
  switch (action.type) {
    case HANDSHAKE_DONE:
      return state.set('id', action.message.id);
    case PLAYER_STATE_RECV: {
      let st = {isAlive: action.message.isAlive, energy: action.message.energy};
      console.log(st);
      return state.set('player', st);
    }
  }

  return state;
};

export const rootReducer = combineReducers({state});
