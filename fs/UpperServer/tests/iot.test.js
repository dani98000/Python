/* eslint-disable no-unused-vars */
// server.js
const request = require('supertest');
const dbUtil = require('./sqlUtility');
// var cookie = require('cookie');

/**
 * Testing post user endpoint
 */
// test('POST /Registration', (done) => {
let jwtCookie;

test('Client Registration when user already exists', async () => {
  const data = {
    email: '1',
    password: 'dummy',
    companyName: 'companyTest122122211322322222122322222'
  };

  await request('http://localhost:8080')
    .post('/Registration')
    .send(data)
    .then(res => {
      expect(res.status).toBe(403);
    });
});

test('Client Registration when user not exists', async () => {
  const data = {
    email: '1',
    password: 'dummy',
    companyName: 'new13122g1221222Company1'
  };

  const res = await request('http://localhost:8080')
    .post('/Registration')
    .send(data)
    .then(res => {
      expect(res.status).toBe(201);
    });
  console.log(dbUtil);
  dbUtil.deleteCompany(data.companyName);
});

/* test
request('http://localhost:8080')
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
