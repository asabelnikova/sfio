'use strict'
import React from 'react';
import {Link, IndexLink} from 'react-router';
import state from "./state.js"
import UserDialog from "./UserDialog.jsx"
import SpawnDialog from "./SpawnDialog.jsx"
import ThreeCanvas from "./ThreeWidget.jsx"
import {syncronize} from "./Field.js"

import 'bootstrap-webpack'

export function Page(props){
  return <div> 
    <ThreeCanvas 
      putNewInput = {props.putNewInput}
      syncronize = {(now)=>{ syncronize(props.state.get('players'),now) }}
    />
    <UserDialog 
      isInGame={isInGame(props.state)}
      onStart = {props.makeHandshake}
    />
    <SpawnDialog 
      isInGame={isInGame(props.state)}
      isAlive = {isAlive(props.state)}
      onSpawn  = {props.spawnPlayer}
    />
  </div>
}

function isAlive(state){
  return state.getIn(['player','parameters','energy','scalar','v']) > 0;
}
function isInGame(state){
  return state.get('id') !== null;
}
