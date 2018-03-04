
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
  var list_name = inputs.list_name || 'list';
  var element_type = inputs.element_type || 'int';

  str = str.replace(/INCLUDE_GUARD/g, list_name.toUpperCase());

  str = str.replace(     /FILENAME/g, list_name);

  str = str.replace(  /LIST_STRUCT/g, list_name);

  str = str.replace( /LIST_TYPEDEF/g, list_name + '_t');

  str = str.replace(  /NODE_STRUCT/g, list_name + '_node');

  str = str.replace( /NODE_TYPEDEF/g, list_name + '_node_t');

  str = str.replace(/VALUE_TYPEDEF/g, inputs.element_type);

  str = str.replace(/LIST_METHOD\([a-z,]*\)/g, function(str) {
    var args_regexp = /\(([a-z,]*)\)/g;
    var match = args_regexp.exec(str);
    if(match[1]) {
      return list_name + '_' + concat(match[1].split(','), style)
    }
    return unhandled;
  });

  return str;
}

