'strict'
import React,{Component} from 'react';
import {Page} from './MainPage.jsx';
import {createStore, applyMiddleware} from 'redux';
import thunk from 'redux-thunk';
import {Provider, connect} from 'react-redux';
import {rootReducer} from './reducers.js';
import networkService from "./networkService.js" 
import {setMousePosition} from "./InputActionsProcessor.js"
import {onMouseCallback} from "./EventLoop.js"
import {wsMessageReceived, 
  makeHandshake, 
  spawnPlayer, 
  putNewInput,
  setMouseCoords} from "./actions.js"


let storeState = createStore(rootReducer, applyMiddleware(thunk));
networkService().onMessage(ab=> storeState.dispatch(wsMessageReceived(ab)));
onMouseCallback(pos=>storeState.dispatch(setMouseCoords(pos)));

export function RootComponent(){
  return <Provider store={storeState} >
    <Root />
  </Provider>
}

const Root = connect(
  mapStateToProps,
  mapDispatchToProps
)(Page);

function mapStateToProps(state){
  return state;
}
function mapDispatchToProps(dispatch){
  let o = {makeHandshake, spawnPlayer, putNewInput};
  let actions = {};
  for(let k in o){
    let fn = o[k];
    actions[k] = function(){return dispatch(fn.apply(null, arguments));}
  }
  return actions;
}
