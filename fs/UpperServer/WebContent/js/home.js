const signUpForm = document.getElementById('sign-up-form')
const signInForm = document.getElementById('sign-in-form')

function transitionToSignUp () {
  signUpForm.style.display = 'block'
  signInForm.style.display = 'none'
}

function transitionToSignIn () {
  signUpForm.style.display = 'none'
  signInForm.style.display = 'block'
}

function initTransitionButtons () {
  document.getElementById('sign-up-transition')
    .addEventListener('click', transitionToSignUp)
  document.getElementById('sign-in-transition')
    .addEventListener('click', transitionToSignIn)
  document.getElementById('sign-in-id')
    .addEventListener('click', transitionToSignIn)
  document.getElementById('sign-up-id')
    .addEventListener('click', transitionToSignUp)
}

window.onload = () => {
  initTransitionButtons()

  document.getElementsByTagName('form')[0].onsubmit = function (event) {
    event.preventDefault()
  }

  document.getElementsByTagName('form')[1].onsubmit = function (event) {
    event.preventDefault()
  }
}

$('.ui.dropdown')
  .dropdown()

function validateSignInForm () {
  const form = document.getElementsByTagName('form')[0]
  const list = document.getElementsByClassName('list')[0]
  const email = document.getElementById('email')
  const password = document.getElementById('password')

  list.innerHTML = ''
  form.classList.remove('warning')

  // eslint-disable-next-line no-useless-escape
  if (!(/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(email.value))) {
    list.innerHTML += '<li>Invalid email address...</li>'
  }
  if (password.value.length < 3) {
    list.innerHTML += '<li>Password too short...</li>'
  }
  if (list.childElementCount > 0) {
    form.classList.add('warning')
    return false
  } else {
    return true
  }
}

function validateSignUpForm () {
  const form = document.getElementsByTagName('form')[1]
  const list = document.getElementsByClassName('list')[1]
  const email = document.getElementsByClassName('email')[0]
  const password = document.getElementsByClassName('password')[0]
  const confirmPassword = document.getElementsByClassName('password')[1]
  const companyName = document.getElementsByClassName('companyName')[0]
  const address = document.getElementsByClassName('address')[0]

  list.innerHTML = ''
  form.classList.remove('warning')

  // eslint-disable-next-line no-useless-escape
  if (!(/^\w+([\.-]?\w+)*@\w+([\.-]?\w+)*(\.\w{2,3})+$/.test(email.value))) {
    list.innerHTML += '<li>Invalid email address...</li>'
    email.parentElement.classList.add('error')
  }

  if (password.value.length < 3) {
    list.innerHTML += '<li>Password too short...</li>'
    password.parentElement.classList.add('error')
  } else if (password.value !== confirmPassword.value) {
    list.innerHTML += '<li>Passwords doesn\'t match!!</li>'
    password.parentElement.classList.add('error')
    confirmPassword.parentElement.classList.add('error')
  }

  if (companyName.value.length < 2) {
    list.innerHTML += '<li>Company Name too short...</li>'
    companyName.parentElement.classList.add('error')
  }

  if (address.value.length < 5) {
    list.innerHTML += '<li>Address too short...</li>'
    address.parentElement.classList.add('error')
  }

  if (list.childElementCount > 0) {
    form.classList.add('warning')
    return false
  } else {
    return true
  }
}

document.getElementsByClassName('submit')[0].addEventListener('click', () => {
  if (!validateSignInForm()) return false
  const email = document.getElementById('email').value
  const password = document.getElementById('password').value
  const form = document.getElementsByTagName('form')[0]
  const list = document.getElementsByClassName('list')[0]
  list.innerHTML = ''
  form.classList.remove('warning')

  var data = JSON.stringify({
    email,
    password
  })

  var url = 'http://localhost:8081/Login'
  var method = 'POST'
  var shouldBeAsync = true
  var request = new XMLHttpRequest()

  request.open(method, url, shouldBeAsync)
  request.onreadystatechange = () => {
    if (request.readyState === window.XMLHttpRequest.DONE && request.status === 200) {
      window.location.href = 'http://localhost:8081/Products'
    } else if (request.readyState === XMLHttpRequest.DONE && request.status === 401) {
      list.innerHTML += '<li>Password or Email are not correct</li>'
      form.classList.add('warning')
    }
  }
  request.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  request.send(data)
})

document.getElementsByClassName('submit')[1].addEventListener('click', () => {
  const fields = document.getElementsByClassName('field');
  [].forEach.call(fields, function (e) {
    e.classList.remove('error')
  })

  if (!validateSignUpForm()) return false

  const email = document.getElementsByClassName('email')[0].value
  const password = document.getElementsByClassName('password')[1].value
  const companyName = document.getElementsByClassName('companyName')[0].value
  const form = document.getElementsByTagName('form')[1]
  const list = document.getElementsByClassName('list')[1]

  list.innerHTML = ''
  form.classList.remove('warning')

  var data = JSON.stringify({
    email,
    password,
    companyName
  })

  var url = 'http://localhost:8081/Registration'
  var method = 'POST'
  var shouldBeAsync = true
  var postRequest = new XMLHttpRequest()

  postRequest.open(method, url, shouldBeAsync)
  postRequest.onreadystatechange = () => {
    if (postRequest.readyState === XMLHttpRequest.DONE && postRequest.status === 201) {
    	console.log('hey');
    	location.href = 'http://localhost:8081/Products'
    } else if (postRequest.readyState === XMLHttpRequest.DONE && postRequest.status === 401) {
      list.innerHTML += '<li>Company already registered</li>'
      form.classList.add('warning')
    }
    
    console.log(postRequest.status);    	
  }
  
  postRequest.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  postRequest.send(data)
})
