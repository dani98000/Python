const mysql = require('mysql');

var con = mysql.createConnection({
  host: 'localhost',
  user: 'daniel',
  password: 'ct,h kvmkhj',
  database: 'IOT'
});

var deleteCompany = function (companyName) {
  console.log('hey');
  con.connect(function (err) {
    if (err) {
      throw err;
    }
    console.log('Connected!');
    var deleteQuery = 'DELETE FROM Companies WHERE companyName = "' + companyName + '"';
    con.query(deleteQuery, function (err, result) {
      if (err) throw err;
      console.log('Number of records deleted: ' + result.affectedRows);
    });
  });
}

module.exports = {
  a: 3
};
