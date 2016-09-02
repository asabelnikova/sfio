let pb = require("protobufjs");
let protoString = require("raw!../proto/gamemessage.proto");
let vec2String = require("raw!../proto/vector2.proto");


let Builder = null;
let Gamemessages = null;
let VectorNS = null;

export function parsePacket(ab) {
  let GM = getMessages();
  let ic = new GM.OutcomingMessage.decode(ab);
  return ic;
}

export function createSpawnPacket(opts) {
  let GM = getMessages();
  let ic = new GM.IncomingMessage(3, null, null, new GM.Spawn);
  return ic.encode();
}

export function createHandshakePacket(name) {
  let GM = getMessages();
  let ic = new GM.IncomingMessage(2, new GM.Handshake(name));
  return ic.encode();
}


const actionMap = {
  thrust: 0,
  shoot: 1,
  skill: 2
};

export function createActionPacket(action) {
  let GM = getMessages();
  let V = getVectorNS();
  let id = actionMap[action.action];
  let skillId = action.skill;
  let onPoint = new V.vec2f(action.onPoint[0], action.onPoint[1]);
  let ic = new GM.IncomingMessage(0, null, new GM.Action(
    id, action.id, onPoint, action.dt, action.startedOn, skillId
  ));
  return ic.encode();
}


function getVectorNS(){
  if (!VectorNS) buildNS();
  return VectorNS;
}
function getMessages() {
  if (!Gamemessages) buildNS();
  return Gamemessages;
}

function buildNS(){
  Builder = pb.newBuilder();
  Builder = pb.protoFromString(vec2String, Builder, "./vector2.proto");
  Builder = pb.protoFromString(protoString, Builder, "gamemessage.proto");
  Gamemessages = Builder.build("gamemessages");
  VectorNS = Builder.build("vec");
}

