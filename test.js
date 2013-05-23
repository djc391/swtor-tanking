var assert = require('assert')
  , sto = require('./index')
  ;


sto.optimizer.optimize(sto.otherData, sto.classData.shadow, {numRelics: 0}, {startingDef: 300, startingShield: 800, startingAbsorb: 1000}, 6033, 70, function (err, results){
  if (err){
    console.log("Error!");
  }
  else {
    console.log(results);
  }
});

console.log();

sto.optimizer.optimize(sto.otherData, sto.classData.shadow, {numRelics: 2, relic1: sto.relicData.arkanian.redoubt, relic2: sto.relicData.conqueror.shield_amp}, {startingDef: 300, startingShield: 800, startingAbsorb: 1000}, 6033, 70, function (err, results){
  if (err){
    console.log("Error!");
  }
  else {
    console.log(results);
  }
});

console.log();

sto.optimizer.optimize(sto.otherData, sto.classData.shadow, {numRelics: 2, relic1: sto.relicData.arkanian.redoubt, relic2: sto.relicData.conqueror.redoubt}, {startingDef: 300, startingShield: 800, startingAbsorb: 1000}, 6033, 70, function (err, results){
  if (err){
    console.log("Error!");
  }
  else {
    console.log(results);
  }
});

console.log();

try {
  sto.optimizer.optimize(); 
} catch (err){
  console.log(err);
}

sto.optimizer.optimize(sto.otherData, sto.classData.shadow, {startingDef: 300, startingShield: 800, startingAbsorb: 1000}, null, function (err, results){
  console.log(err);
  console.log(results);
});
