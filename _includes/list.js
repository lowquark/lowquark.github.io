
var regexp = {}
regexp['INCLUDE_GUARD'] = /INCLUDE_GUARD/g;
regexp['FILENAME']      = /FILENAME/g;
regexp['LIST_STRUCT']   = /LIST_STRUCT/g;
regexp['LIST_TYPEDEF']  = /LIST_TYPEDEF/g;
regexp['NODE_STRUCT']   = /NODE_STRUCT/g;
regexp['NODE_TYPEDEF']  = /NODE_TYPEDEF/g;
regexp['VALUE_TYPEDEF'] = /VALUE_TYPEDEF/g;
regexp['LIST_METHOD']   = /LIST_METHOD\([a-z,]*\)/g;

var unhandled = '<UNHANDLED>';

var replace = {}
replace['INCLUDE_GUARD'] = unhandled;
replace['FILENAME']      = unhandled;
replace['LIST_STRUCT']   = unhandled;
replace['LIST_TYPEDEF']  = unhandled;
replace['NODE_STRUCT']   = unhandled;
replace['NODE_TYPEDEF']  = unhandled;
replace['VALUE_TYPEDEF'] = unhandled;
replace['LIST_METHOD']   = unhandled;

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
function typedef_ify(name, style) {
  if(style == 'old_school_t') {
    return name + '_t';
  } else {
    return name;
  }
}

function process_string(str, inputs, style) {
  if(inputs.list_type) {
    var list_type = inputs.list_type;

    replace['INCLUDE_GUARD'] = list_type.toUpperCase();
    replace['FILENAME']      = list_type;

    replace['LIST_STRUCT']   = list_type;
    replace['LIST_TYPEDEF']  = typedef_ify(replace['LIST_STRUCT'], style);

    replace['NODE_STRUCT']   = concat([list_type, 'node'], style);
    replace['NODE_TYPEDEF']  = typedef_ify(replace['NODE_STRUCT'], style);

    replace['LIST_METHOD']   = function(str) {
      var args_regexp = /\(([a-z,]*)\)/g;
      var match = args_regexp.exec(str);
      if(match[1]) {
        var words = match[1].split(',');
        words.unshift(list_type);
        return concat(words, style)
      }
      return unhandled;
    };
  }

  if(inputs.element_type) {
    replace['VALUE_TYPEDEF'] = inputs.element_type;
  }

  function do_replace(name) {
    str = str.replace(regexp[name], replace[name]);
  }

  do_replace('INCLUDE_GUARD');
  do_replace('FILENAME');
  do_replace('LIST_STRUCT');
  do_replace('LIST_TYPEDEF');
  do_replace('NODE_STRUCT');
  do_replace('NODE_TYPEDEF');
  do_replace('VALUE_TYPEDEF');
  do_replace('LIST_METHOD');

  return str;
}

