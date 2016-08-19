'strict'
import React,{Component} from 'react';
import {Page} from './MainPage.jsx';
import {createStore, applyMiddleware} from 'redux';
import thunk from 'redux-thunk';
import {Provider, connect} from 'react-redux';
import {rootReducer} from './reducers.js';
import networkService from "./networkService.js" 
import {wsMessageReceived, 
  makeHandshake, 
  spawnPlayer, 
  setMouseCoords} from "./actions.js"


let storeState = createStore(rootReducer, applyMiddleware(thunk));

networkService().onMessage(ab=> storeState.dispatch(wsMessageReceived(ab)));

document.addEventListener('mousemove', function(evt){
  storeState.dispatch(setMouseCoords(evt.clientX, evt.clientY));
})

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
  let o = {makeHandshake, spawnPlayer};
  let actions = {};
  for(let k in o){
    let fn = o[k];
    actions[k] = function(){return dispatch(fn.apply(null, arguments));}
  }
  return actions;
}
