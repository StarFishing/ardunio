$(function() {
  $('.open i').click(function() {
    if (this.id == 'close') {
      $.post('/fclose', this.id, function(data, status) {})
    }
    if (this.id == 'open') {
      $.post('/fopen', this.id, function(data, status) {})
    }
  })

  $('.open2 i').click(function() {
    if (this.id == 'close2') {
      $.post('/lclose', this.id, function(data, status) {})
    }
    if (this.id == 'open2') {
      $.post('/lopen', this.id, function(data, status) {})
    }
  })
})
