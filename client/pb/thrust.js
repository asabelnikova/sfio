/**
 * @fileoverview
 * @enhanceable
 * @public
 */
// GENERATED CODE -- DO NOT EDIT!

goog.provide('proto.gamemessages.Thrust');

goog.require('jspb.Message');
goog.require('proto.vec.vec2f');


/**
 * Generated by JsPbCodeGenerator.
 * @param {Array=} opt_data Optional initial data array, typically from a
 * server response, or constructed directly in Javascript. The array is used
 * in place and becomes part of the constructed object. It is not cloned.
 * If no data is provided, the constructed object will be empty, but still
 * valid.
 * @extends {jspb.Message}
 * @constructor
 */
proto.gamemessages.Thrust = function(opt_data) {
  jspb.Message.initialize(this, opt_data, 0, -1, null, null);
};
goog.inherits(proto.gamemessages.Thrust, jspb.Message);
if (goog.DEBUG && !COMPILED) {
  proto.gamemessages.Thrust.displayName = 'proto.gamemessages.Thrust';
}


if (jspb.Message.GENERATE_TO_OBJECT) {
/**
 * Creates an object representation of this proto suitable for use in Soy templates.
 * Field names that are reserved in JavaScript and will be renamed to pb_name.
 * To access a reserved field use, foo.pb_<name>, eg, foo.pb_default.
 * For the list of reserved names please see:
 *     com.google.apps.jspb.JsClassTemplate.JS_RESERVED_WORDS.
 * @param {boolean=} opt_includeInstance Whether to include the JSPB instance
 *     for transitional soy proto support: http://goto/soy-param-migration
 * @return {!Object}
 */
proto.gamemessages.Thrust.prototype.toObject = function(opt_includeInstance) {
  return proto.gamemessages.Thrust.toObject(opt_includeInstance, this);
};


/**
 * Static version of the {@see toObject} method.
 * @param {boolean|undefined} includeInstance Whether to include the JSPB
 *     instance for transitional soy proto support:
 *     http://goto/soy-param-migration
 * @param {!proto.gamemessages.Thrust} msg The msg instance to transform.
 * @return {!Object}
 */
proto.gamemessages.Thrust.toObject = function(includeInstance, msg) {
  var f, obj = {
    id: msg.getId(),
    direction: (f = msg.getDirection()) && proto.vec.vec2f.toObject(includeInstance, f),
    time: msg.getTime()
  };

  if (includeInstance) {
    obj.$jspbMessageInstance = msg;
  }
  return obj;
};
}


/**
 * Creates a deep clone of this proto. No data is shared with the original.
 * @return {!proto.gamemessages.Thrust} The clone.
 */
proto.gamemessages.Thrust.prototype.cloneMessage = function() {
  return /** @type {!proto.gamemessages.Thrust} */ (jspb.Message.cloneMessage(this));
};


/**
 * optional int32 id = 1;
 * @return {number}
 */
proto.gamemessages.Thrust.prototype.getId = function() {
  return /** @type {number} */ (jspb.Message.getFieldProto3(this, 1, 0));
};


/** @param {number} value  */
proto.gamemessages.Thrust.prototype.setId = function(value) {
  jspb.Message.setField(this, 1, value);
};


/**
 * optional vec.vec2f direction = 2;
 * @return {proto.vec.vec2f}
 */
proto.gamemessages.Thrust.prototype.getDirection = function() {
  return /** @type{proto.vec.vec2f} */ (
    jspb.Message.getWrapperField(this, proto.vec.vec2f, 2));
};


/** @param {proto.vec.vec2f|undefined} value  */
proto.gamemessages.Thrust.prototype.setDirection = function(value) {
  jspb.Message.setWrapperField(this, 2, value);
};


proto.gamemessages.Thrust.prototype.clearDirection = function() {
  this.setDirection(undefined);
};


/**
 * Returns whether this field is set.
 * @return{!boolean}
 */
proto.gamemessages.Thrust.prototype.hasDirection = function() {
  return jspb.Message.getField(this, 2) != null;
};


/**
 * optional float time = 3;
 * @return {number}
 */
proto.gamemessages.Thrust.prototype.getTime = function() {
  return /** @type {number} */ (jspb.Message.getFieldProto3(this, 3, 0));
};


/** @param {number} value  */
proto.gamemessages.Thrust.prototype.setTime = function(value) {
  jspb.Message.setField(this, 3, value);
};


