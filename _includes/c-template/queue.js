
function concat(array, style) {
  if(style == 'old_school' || style == 'old_school_t') {
    return array.join('_');
  } else if(style == 'camelCase') {
    for(var i = 1 ; i < array.length ; i ++) {
      array[i] = array[i][0].toUpperCase() + array[i].substring(1)
    }
    return array.join('');
  }
}

function process_string(str, inputs, style) {
  var queue_name = inputs.queue_name || 'queue';
  var element_type = inputs.element_type || 'int';

  str = str.replace(/INCLUDE_GUARD/g, queue_name.toUpperCase());

  str = str.replace(     /FILENAME/g, queue_name);

  str = str.replace( /QUEUE_STRUCT/g, queue_name);

  str = str.replace(/QUEUE_TYPEDEF/g, queue_name + '_t');

  str = str.replace(/VALUE_TYPEDEF/g, inputs.element_type);

  str = str.replace(/QUEUE_METHOD\([a-z,]*\)/g, function(str) {
    var args_regexp = /\(([a-z,]*)\)/g;
    var match = args_regexp.exec(str);
    if(match[1]) {
      return queue_name + '_' + concat(match[1].split(','), style)
    }
    return unhandled;
  });

  console.log(str);

  return str;
}

