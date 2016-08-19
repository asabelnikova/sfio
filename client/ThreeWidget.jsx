import React, {Component} from 'react';
import ReactDOM from 'react-dom';
import THREE from 'three';
import mainLoop from "./EventLoop.js";

export default class ThreeCanvas extends Component{
  constructor(props){
    super(props);

  }
  componentDidMount(){
    this.node = ReactDOM.findDOMNode(this);
    this.node.width = window.innerWidth;
    this.node.height = window.innerHeight;
    this.renderer = new THREE.WebGLRenderer({canvas: this.node});
    mainLoop(()=>console.log('render fn'), (keys)=>{
      if(keys.length > 0) console.log("dump keys fn", keys.map(a=>`${a.code}: ${a.dt}`))
    });

  }
  render(){
    return <canvas />
  }
}
