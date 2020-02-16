/* eslint-disable no-unused-vars */
/* eslint-disable no-unused-expressions */
// server.js
const request = require('supertest');
var cookie = require('cookie');

/**
 * Testing post user endpoint
 */
// test('POST /Registration', (done) => {
const data = {
  email: '1',
  password: 'dummy',
  companyName: 'companyTest122122211322322222122322222'
};

let jwtCookie;

/* test('sending a post request without a cookie', async () => {
  request('http://localhost:8080')
    .post('/Registration')
    .send(data)
    .end(function (err, res) {
      expect(res.status.to).tobe
      if(err) {
        console.log('fuck');
      }
    });
}); */

test('sum 2+2 to equal 4', () => {
  (expect(2+2)).toBe(4);
});

/* request('http://localhost:8080')
  .post('/Registration')
  .send(data)
  .end(function (err, res) {
    jwtCookie = res.headers['set-cookie'][0];
    console.log(cookie.parse(jwtCookie)['JWT-TOKEN']);
    if (err || !res.ok) {
      console.log('fuck');
      console.log(res.status);
    } else {
      console.log('all good');

      request('http://localhost:8080')
        .get('/Products')
        .set('cookie', jwtCookie)
        .end(function (err, res) {
          if (err || !res.ok) {
            console.log('fuck');
            console.log(res.status);
            console.log(res.headers['set-cookie']);
          } else {
            console.log('all good');
            console.log(res.headers['set-cookie']);
          }
        });
    }
  });
*/
