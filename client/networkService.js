
let socket = null;
let callbacks = [];



export default function() {
  if (socket === null) {
    initSocket();
  }

  return {
    send: function(arrayBuffer) { socket.send(arrayBuffer); },
        onMessage: (fn) => callbacks.push(fn)
  }
}

function initSocket() {
  let loc = window.location;
  let proto = 'ws:';
  let addr = `${proto}//${loc.hostname}:9002/`;
  console.log("Addr", addr);
  socket = new WebSocket(addr);
  socket.onopen = function() { console.log("AAAA"); };
  socket.onmessage = (event) => {
    let fr = new FileReader;
    fr.onload = () => callbacks.map(fn => fn(fr.result));
    fr.readAsArrayBuffer(event.data);
  };
}
