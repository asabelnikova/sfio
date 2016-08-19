'use strict'

import React from 'react';
import networkService from './networkService.js';
import s from './styles/main.styl'

let currentUsername = '';
export default function({onStart, isInGame}){
  if(isInGame) return <span/>;
  return <div className={s.fixedDialog}>
    <div className='well'> 
      <div className='form'>
        <div className='form-group'>
          <label  >Username:</label>
          <input id='username' 
            type="text" 
            className="form-control"
            onChange={ usernameChanged }
          />
        </div>
        <div>
          <button className = 'btn btn-primary' 
            onClick={()=>{onStart(currentUsername);}}> 
            Start
        </button>
        </div>
      </div>
    </div>
  </div>
}

function usernameChanged(evt){
  currentUsername = evt.currentTarget.value;
}
