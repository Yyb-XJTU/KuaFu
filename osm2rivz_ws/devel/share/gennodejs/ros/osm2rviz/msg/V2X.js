// Auto-generated. Do not edit!

// (in-package osm2rviz.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class V2X {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Yellow = null;
      this.Red = null;
      this.Black = null;
    }
    else {
      if (initObj.hasOwnProperty('Yellow')) {
        this.Yellow = initObj.Yellow
      }
      else {
        this.Yellow = [];
      }
      if (initObj.hasOwnProperty('Red')) {
        this.Red = initObj.Red
      }
      else {
        this.Red = [];
      }
      if (initObj.hasOwnProperty('Black')) {
        this.Black = initObj.Black
      }
      else {
        this.Black = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type V2X
    // Serialize message field [Yellow]
    bufferOffset = _arraySerializer.int32(obj.Yellow, buffer, bufferOffset, null);
    // Serialize message field [Red]
    bufferOffset = _arraySerializer.int32(obj.Red, buffer, bufferOffset, null);
    // Serialize message field [Black]
    bufferOffset = _arraySerializer.int32(obj.Black, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type V2X
    let len;
    let data = new V2X(null);
    // Deserialize message field [Yellow]
    data.Yellow = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [Red]
    data.Red = _arrayDeserializer.int32(buffer, bufferOffset, null)
    // Deserialize message field [Black]
    data.Black = _arrayDeserializer.int32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.Yellow.length;
    length += 4 * object.Red.length;
    length += 4 * object.Black.length;
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'osm2rviz/V2X';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'a7304ed0a871552fc04b10784eeafcb6';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int32[] Yellow
    int32[] Red
    int32[] Black
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new V2X(null);
    if (msg.Yellow !== undefined) {
      resolved.Yellow = msg.Yellow;
    }
    else {
      resolved.Yellow = []
    }

    if (msg.Red !== undefined) {
      resolved.Red = msg.Red;
    }
    else {
      resolved.Red = []
    }

    if (msg.Black !== undefined) {
      resolved.Black = msg.Black;
    }
    else {
      resolved.Black = []
    }

    return resolved;
    }
};

module.exports = V2X;
