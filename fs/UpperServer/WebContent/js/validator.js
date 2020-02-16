/* eslint-disable semi */
function addField (fieldName, valid, invalid) {
  this.validMap.set(fieldName, {
    valid,
    invalid,
    tests: [],
    errors: []
  });
}

function addTest (fieldName, testFunc, errorMsg) {
  const newValue = this.validMap.get(fieldName);
  newValue.tests.push({ testFunc, errorMsg });

  this.validMap.set(fieldName, newValue);
}

function validate (values) {
  return new Promise((resolve, reject) => {
    this.errors = [];

    Object.keys(values).forEach((fieldName) => {
      const currValue = this.validMap.get(fieldName);
      const { tests } = currValue;

      currValue.errors = [];

      tests.forEach((test) => {
        if (!test.testFunc(values[fieldName])) {
          currValue.errors.push(test.errorMsg);
          this.errors.push(test.errorMsg);
        }
      });

      if (currValue.errors.length !== 0) {
        currValue.invalid && currValue.invlaid(currValue.errors);
      } else {
        currValue.invalid && currValue.valid();
      }
    });

    if (this.errors.length === 0) {
      resolve();
    } else {
      reject(this.errors);
    }
  });
}

window.Validator = function Validator () {
  this.validMap = new Map();
  this.compositeTests = [];
  this.errors = [];
  this.addField = addField;
  this.addTest = addTest;
  // this.addCompositeTest = addCompositeTest;
  this.validate = validate;
}
