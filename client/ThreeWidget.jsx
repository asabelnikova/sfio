import React, {Component} from 'react';
import ReactDOM from 'react-dom';
import THREE from 'three';
import mainLoop,{setZeroTime, setCamera, onMouseCallback} from "./EventLoop.js";
import {setScene} from "./Field.js";


export default class ThreeCanvas extends Component{
  constructor(props){
    super(props);
    this.objects = {};
    this.scene = new THREE.Scene();
    setScene(this.scene);
    let aspect = window.innerWidth/window.innerHeight;
    this.camera = new THREE.PerspectiveCamera(45, aspect, 0.01, 1000);
    setCamera(this.camera)
    this.camera.position.z = 5;
    this.camera.lookAt(new THREE.Vector3(0, 0, 0));
  }
  initDebugging(){
    this.debugMouseMesh = new THREE.Mesh(new THREE.CircleBufferGeometry(0.1,36), 
      new THREE.MeshBasicMaterial({
      color:0xff00ff
    }))
    let mesh = this.debugMouseMesh;
    mesh.position.z = 0;
    this.scene.add(mesh);
    onMouseCallback(pos=>{
      mesh.position.x = pos.x;
      mesh.position.y = pos.y;
    })
  }


  componentWillReceiveProps(props){
  }

  componentDidMount(){
    this.node = ReactDOM.findDOMNode(this);
    this.node.width = window.innerWidth;
    this.node.height = window.innerHeight;
    this.renderer = new THREE.WebGLRenderer({canvas: this.node});
    this.initDebugging();
    mainLoop((now)=>{
      this.props.syncronize(now);
      this.renderer.render(this.scene, this.camera);
    }, (keys)=>{if(keys.length > 0) this.props.putNewInput(keys)});

  }
  render(){
    return <canvas />
  }
}
