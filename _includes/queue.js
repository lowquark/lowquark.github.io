
var regexp = {}
regexp['INCLUDE_GUARD'] = /INCLUDE_GUARD/g;
regexp['FILENAME']      = /FILENAME/g;
regexp['QUEUE_STRUCT']   = /QUEUE_STRUCT/g;
regexp['QUEUE_TYPEDEF']  = /QUEUE_TYPEDEF/g;
regexp['VALUE_TYPEDEF'] = /VALUE_TYPEDEF/g;
regexp['QUEUE_METHOD']   = /QUEUE_METHOD\([a-z,]*\)/g;

var unhandled = '<UNHANDLED>';

var replace = {}
replace['INCLUDE_GUARD'] = unhandled;
replace['FILENAME']      = unhandled;
replace['QUEUE_STRUCT']   = unhandled;
replace['QUEUE_TYPEDEF']  = unhandled;
replace['VALUE_TYPEDEF'] = unhandled;
replace['QUEUE_METHOD']   = unhandled;

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
  if(inputs.queue_type) {
    var queue_type = inputs.queue_type;

    replace['INCLUDE_GUARD'] = queue_type.toUpperCase();
    replace['FILENAME']      = queue_type;

    replace['QUEUE_STRUCT']   = queue_type;
    replace['QUEUE_TYPEDEF']  = typedef_ify(replace['QUEUE_STRUCT'], style);

    replace['QUEUE_METHOD']   = function(str) {
      var args_regexp = /\(([a-z,]*)\)/g;
      var match = args_regexp.exec(str);
      if(match[1]) {
        var words = match[1].split(',');
        words.unshift(queue_type);
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
  do_replace('QUEUE_STRUCT');
  do_replace('QUEUE_TYPEDEF');
  do_replace('VALUE_TYPEDEF');
  do_replace('QUEUE_METHOD');

  return str;
}

