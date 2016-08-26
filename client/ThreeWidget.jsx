import React, {Component} from 'react';
import ReactDOM from 'react-dom';
import THREE from 'three';
import mainLoop,{setZeroTime} from "./EventLoop.js";
import {setScene} from "./Field.js";


export default class ThreeCanvas extends Component{
  constructor(props){
    super(props);
    this.objects = {};
    this.scene = new THREE.Scene();
    setScene(this.scene);
    let aspect = window.innerWidth/window.innerHeight;
    this.camera = new THREE.PerspectiveCamera(45, aspect, 0.01, 1000);
    this.camera.position.z = 5;
    this.camera.lookAt(new THREE.Vector3(0, 0, 0));

    //this. fakePlayer = {
    //id: 100500,
    //actions:[],
    //initial:{position:[0,0], velocity:[0,0]},
    //}
    

  }

  componentWillReceiveProps(props){
  }

  componentDidMount(){
    this.node = ReactDOM.findDOMNode(this);
    this.node.width = window.innerWidth;
    this.node.height = window.innerHeight;
    this.renderer = new THREE.WebGLRenderer({canvas: this.node});
    mainLoop(()=>{
      this.props.syncronize();
      this.renderer.render(this.scene, this.camera);
    }, (keys)=>{if(keys.length > 0) this.props.putNewInput(keys)});

  }
  render(){
    return <canvas />
  }
}
