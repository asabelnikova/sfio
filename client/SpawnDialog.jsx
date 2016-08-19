
'use strict'

import React from 'react';
import networkService from './networkService.js';
import s from './styles/main.styl'

export default function({onSpawn, isAlive, isInGame}){
  if(!isInGame) return <span/>;
  if(isAlive) return <span/>;
  return <div className={s.fixedDialog}>
    <div className='well'> 
      <div className='form'>
        <div>
          <button className = 'btn btn-primary' 
            onClick={()=>{onSpawn();}}> 
            Spawn
        </button>
        </div>
      </div>
    </div>
  </div>
}

