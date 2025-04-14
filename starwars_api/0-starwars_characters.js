#!/usr/bin/node
const request = require('request');

const filmID = process.argv[2];
if (!filmID || isNaN(filmID)) {
  console.log('Invalid film ID, ./0-starwars_characters.js <film_id>');
  process.exit(1);
}

const url = 'https://swapi-api.hbtn.io/api/films/' + filmID;

request(url, (error, response, body) => {
  if (error) {
    console.error('Error: ', error);
    return;
  }

  const charData = JSON.parse(body).characters;

  const printCharacters = (index) => {
    if (index >= charData.length) {
      return;
    }
    request(charData[index], (error, response, body) => {
      if (error) {
        console.error('Error: ', error);
        return;
      }
      console.log(JSON.parse(body).name);
      printCharacters(index + 1);
    });
  };
  printCharacters(0);
});
