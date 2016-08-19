'strict';
import networkService from "./networkService.js";
import {
  createHandshakePacket,
  createSpawnPacket,
  parsePacket
} from "./PacketManager.js";


export const SET_MOUSE_COORDS = 'SET_MOUSE_COORDS';
export function setMouseCoords(x, y) {
  return { type: SET_MOUSE_COORDS, x, y }
}

export const SPAWN_PLAYER = 'SPAWN_PLAYER';
export function spawnPlayer(opts) {
  return dispatch => {
    dispatch({type: SPAWN_PLAYER, opts});
    let packet = createSpawnPacket(opts);
    networkService().send(packet.buffer);
  }
}

export const MAKE_HANDSHAKE = 'MAKE_HANDSHAKE';
export function makeHandshake(withName) {
  return dispatch => {
    dispatch({type: MAKE_HANDSHAKE, withName});
    let packet = createHandshakePacket(withName);

    networkService().send(packet.buffer);
  }
}
export const HANDSHAKE_DONE = 'HANDSHAKE_DONE';
export const SCENE_RECEIVED = 'SCENE_RECEIVED';
export const PLAYER_STATE_RECV = 'PLAYER_STATE_RECV';
export function wsMessageReceived(ab) {
  let message = parsePacket(ab);
  console.log(message);
  switch (message.type) {
    case 0:  // handshake
      return {type: HANDSHAKE_DONE, message: message.handshakeResponse};

    case 1:  // scene
      return {type: SCENE_RECEIVED, message: message.scene};

    case 2:  // scene
      return {type: PLAYER_STATE_RECV, message: message.playerState};
  }
  return message;
}
