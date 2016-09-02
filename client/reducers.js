import {combineReducers} from 'redux';
import {List, Map, fromJS} from 'immutable';
import {
  PUT_NEW_INPUT,
  PLAYER_STATE_RECV,
  HANDSHAKE_DONE,
  SET_MOUSE_COORDS
} from './actions.js';
import {setZeroTime} from "./EventLoop.js";
import {processPlayerInputs} from "./InputActionsProcessor.js";
import networkService from "./networkService.js";
import {createActionPacket} from "./PacketManager.js";

const defaultState = {
  id: null,
  player: {
    energy: 0,
    isAlive: false,
    actions: [],
    parameters:{
      position:{
        v:[0,0], dv:[0,0],
        calculatedAt: 0,
      }
    },
  },
  players: {},
  zeroTime: 0
};

function state(state = fromJS(defaultState), action) {
  switch (action.type) {
    case HANDSHAKE_DONE: {
      setZeroTime(action.message.zeroTime);
      return state.set('id', action.message.id)
          .set('zeroTime', action.message.zeroTime);
    }
    case PLAYER_STATE_RECV: {
      let player = fromJS(action.message.toRaw()).set('actions', new List());
      let id = state.get('id');
      return state.set('player', player).mergeIn(['players'], {[id]: player});
    }
    case SET_MOUSE_COORDS: {
      return state.set("mouse", [action.x, action.y]);
    }
    case PUT_NEW_INPUT: {
      let inputs = action.inputActions;
      let id = state.get('id');
      if (!id) return state;
      
      let actions = processPlayerInputs(id, inputs);
      actions.map(a => networkService().send(createActionPacket(a)));
      return state.updateIn(
          ['players', id.toString(), 'actions'], List(),
          l => l.push(...actions))
    }
  }

  return state;
};

export const rootReducer = combineReducers({state});
