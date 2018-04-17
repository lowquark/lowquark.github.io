
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
  var map_name = inputs.map_name || 'list';
  var element_type = inputs.element_type || 'int';

  str = str.replace(/INCLUDE_GUARD/g, map_name.toUpperCase());

  str = str.replace(     /FILENAME/g, map_name);

  str = str.replace(   /MAP_STRUCT/g, map_name);

  str = str.replace(  /MAP_TYPEDEF/g, map_name + '_t');

  str = str.replace( /ENTRY_STRUCT/g, map_name + '_entry');

  str = str.replace(/ENTRY_TYPEDEF/g, map_name + '_entry_t');

  str = str.replace(  /KEY_TYPEDEF/g, map_name + '_hash_t');

  str = str.replace(/VALUE_TYPEDEF/g, inputs.element_type);

  str = str.replace( /HASH_TYPEDEF/g, map_name + '_hash_t');

  str = str.replace(/MAP_METHOD\([a-z,]*\)/g, function(str) {
    var args_regexp = /\(([a-z,]*)\)/g;
    var match = args_regexp.exec(str);
    if(match[1]) {
      return map_name + '_' + concat(match[1].split(','), style)
    }
    return unhandled;
  });

  return str;
}

