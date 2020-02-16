/* eslint-disable no-unused-vars */
/* eslint-disable camelcase */
var addButton = document.getElementById('addProduct')
var favDialog = document.getElementsByClassName('modal')[0]
var confirmBtn = document.getElementById('confirmBtn')
var closeBtn = document.getElementsByClassName('close-button')[0]
var productName = document.getElementsByClassName('productName')[0]
var category = document.getElementsByClassName('category')[0]
var catalogNumber = document.getElementsByClassName('catalogNumber')[0]
var description = document.getElementsByClassName('description')[1]
var tableRef = document.getElementsByClassName('products-table')[0].getElementsByTagName('tbody')[0]
var id = 0
var curr_id = id
var state = 'add'

window.onload = function () {
  id = tableRef.rows.length
}

document.getElementById('sign-out-id').addEventListener('click', () => {
  var url = 'http://localhost:8081/Logout'
  var method = 'POST'
  var shouldBeAsync = true
  var request = new XMLHttpRequest()

  request.onload = function () {
    var status = request.status // HTTP response status, e.g., 200 for "200 OK"
    var data = request.responseText // Returned data, e.g., an HTML document.
  }

  request.open(method, url, shouldBeAsync)
  request.onreadystatechange = () => {
    if (request.readyState === XMLHttpRequest.DONE && request.status === 200) {
      window.location.href = 'http://localhost:8081/Registration'
    } else {
      console.log(request.status)
    }
  }
  request.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  request.send()
})

addButton.addEventListener('click', () => {
  $('.ui.modal').modal('show')
})

function deleteProduct(id) {	
	const catNumber = tableRef.rows[id-1].cells[3].innerText
	
	var data = JSON.stringify({
		catNumber
	})

	var url = 'http://localhost:8081/Products'
	var method = 'DELETE'
	var shouldBeAsync = true
	var request = new XMLHttpRequest()

	request.open(method, url, shouldBeAsync)
	request.onreadystatechange = () => {
		if (request.readyState === window.XMLHttpRequest.DONE && request.status === 200) {
			const removeBtn = document.getElementById(id)
			const rowNum = removeBtn.parentElement.parentElement.rowIndex - 1
			tableRef.deleteRow(rowNum)
			resetIDs(rowNum)	
		} else if (request.readyState === XMLHttpRequest.DONE && request.status !== 200) {
			console.log(request.status)
		}
	}
	
  	request.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
  	request.send(data)
}

confirmBtn.addEventListener('click', () => {
  if (!validateForm()) return false

  const prodName = productName.value
  const catName = category.value
  const catNumber = catalogNumber.value
  const desc = description.value
  
  var data = JSON.stringify({
	  prodName,
	  catName,
	  catNumber,
	  desc
  })
  
  if (state === 'add') {
    var url = 'http://localhost:8081/Products'
    var method = 'POST'
    var shouldBeAsync = true
    var request = new XMLHttpRequest()

    request.onload = function () {
      var status = request.status
      var data = request.responseText 
    }

    request.open(method, url, shouldBeAsync)
    request.onreadystatechange = () => {
      if (request.readyState === XMLHttpRequest.DONE && request.status === 201) {
        const newRow = tableRef.insertRow(tableRef.rows.length)
        newRow.insertCell(0).innerText = tableRef.rows.length
        newRow.insertCell(1).innerText = prodName
        newRow.insertCell(2).innerText = catName
        newRow.insertCell(3).innerText = catNumber
        newRow.insertCell(4).innerText = desc
        newRow.innerHTML += '<td class="collapsing">' +
                    '<button onclick="editRow(\'' + (id) + '\')" id=' + (id) + ' class="ui button circular icon"><i class="edit outline icon"></i></button>' +
                    '<button onclick="deleteProduct(\'' + (id) + '\')" class="ui button circular icon"><i class="trash alternate outline icon"></i></button>' +
                    '</td>'
        ++id
      } else {
        console.log(request.status)
      }
    }
    request.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
    request.send(data)
  } else if (state === 'edit') {
      var url = 'http://localhost:8081/Products'
      var method = 'PATCH'
      var shouldBeAsync = true
      var request = new XMLHttpRequest()

      request.onload = function () {
        var status = request.status
        var data = request.responseText 
      }

      request.open(method, url, shouldBeAsync)
      request.onreadystatechange = () => {
        if (request.readyState === XMLHttpRequest.DONE && request.status === 200) {
            tableRef.rows[curr_id - 1].cells[1].innerText = prodName
            tableRef.rows[curr_id - 1].cells[2].innerText = catName
            tableRef.rows[curr_id - 1].cells[4].innerText = desc
            state = 'add'
        } else if(request.readyState === XMLHttpRequest.DONE && request.status !== 200){
          console.log(request.status)
        }
      }
      request.setRequestHeader('Content-Type', 'application/json;charset=UTF-8')
      request.send(data)    
  }
  clearDialog()
})

function clearDialog () {
  productName.value = ''
  category.value = ''
  catalogNumber.value = ''
  description.value = ''
}

function editRow (id) {
  $('.ui.modal').modal('show')
  const button = document.getElementById(id)
  productName.value = tableRef.rows[button.parentElement.parentElement.rowIndex - 1].cells[1].innerText
  category.value = tableRef.rows[button.parentElement.parentElement.rowIndex - 1].cells[2].innerText
  catalogNumber.value = tableRef.rows[button.parentElement.parentElement.rowIndex - 1].cells[3].innerText
  description.value = tableRef.rows[button.parentElement.parentElement.rowIndex - 1].cells[4].innerText
  state = 'edit'
  curr_id = id
}

function resetIDs (id) {
  const end = tableRef.rows.length - 1

  for (let start = id; start <= end; start++) {
    tableRef.rows[start].cells[0].innerText -= 1
  }
}

function validateForm () {
  const form = document.getElementsByClassName('form')[0]
  const list = document.getElementsByClassName('list')[0]

  list.innerHTML = ''
  form.classList.remove('warning')

  if (productName.value.length < 3) {
    list.innerHTML += '<li>Product name too short...</li>'
  }
  if (category.value.length < 3) {
    list.innerHTML += '<li>category name too short...</li>'
  }
  if (catalogNumber.value.length < 3) {
    list.innerHTML += '<li>Catalog number too short...</li>'
  }
  if (description.value.length < 10) {
    list.innerHTML += '<li>Description too short...</li>'
  }
  if (list.childElementCount > 0) {
    form.classList.add('warning')
    $('.ui.modal').modal({
      closable: false,
      onApprove: function () {
        return false
      }
    }).modal('show')

    return false
  } else {
    $('.ui.modal').modal({
      onApprove: function () {
        return true
      }
    }).modal('show')

    return true
  }
}
