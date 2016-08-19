let pb = require("protobufjs");
let protoString = require("raw!../proto/gamemessage.proto");
let vec2String = require("raw!../proto/vector2.proto");


let Builder = null;
let Gamemessages = null;

export function parsePacket(ab) {
  let GM = getMessages();
  let ic = new GM.OutcomingMessage.decode(ab);
  return ic;
}

export function createSpawnPacket(opts) {
  let GM = getMessages();
  let ic = new GM.IncomingMessage(3, null, null, null, new GM.Spawn);
  return ic.encode();
}

export function createHandshakePacket(name) {
  let GM = getMessages();
  let ic = new GM.IncomingMessage(2, new GM.Handshake(name));
  return ic.encode();
}


function getMessages() {
  if (!Gamemessages) Builder = pb.newBuilder();
  Builder = pb.protoFromString(vec2String, Builder, "./vector2.proto");
  Builder = pb.protoFromString(protoString, Builder, "gamemessage.proto");
  Gamemessages = Builder.build("gamemessages");
  return Gamemessages;
}
