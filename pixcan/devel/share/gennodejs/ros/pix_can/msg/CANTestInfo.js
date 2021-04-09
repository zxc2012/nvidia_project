// Auto-generated. Do not edit!

// (in-package pix_can.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class CANTestInfo {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.header = null;
      this.current_wheel = null;
      this.target_wheel = null;
    }
    else {
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
      if (initObj.hasOwnProperty('current_wheel')) {
        this.current_wheel = initObj.current_wheel
      }
      else {
        this.current_wheel = 0;
      }
      if (initObj.hasOwnProperty('target_wheel')) {
        this.target_wheel = initObj.target_wheel
      }
      else {
        this.target_wheel = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CANTestInfo
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    // Serialize message field [current_wheel]
    bufferOffset = _serializer.uint16(obj.current_wheel, buffer, bufferOffset);
    // Serialize message field [target_wheel]
    bufferOffset = _serializer.uint16(obj.target_wheel, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CANTestInfo
    let len;
    let data = new CANTestInfo(null);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    // Deserialize message field [current_wheel]
    data.current_wheel = _deserializer.uint16(buffer, bufferOffset);
    // Deserialize message field [target_wheel]
    data.target_wheel = _deserializer.uint16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'pix_can/CANTestInfo';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'f942539659fc3310c68f769b65513a00';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    Header header
    uint16 current_wheel
    uint16 target_wheel
    
    ================================================================================
    MSG: std_msgs/Header
    # Standard metadata for higher-level stamped data types.
    # This is generally used to communicate timestamped data 
    # in a particular coordinate frame.
    # 
    # sequence ID: consecutively increasing ID 
    uint32 seq
    #Two-integer timestamp that is expressed as:
    # * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
    # * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
    # time-handling sugar is provided by the client library
    time stamp
    #Frame this data is associated with
    string frame_id
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CANTestInfo(null);
    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    if (msg.current_wheel !== undefined) {
      resolved.current_wheel = msg.current_wheel;
    }
    else {
      resolved.current_wheel = 0
    }

    if (msg.target_wheel !== undefined) {
      resolved.target_wheel = msg.target_wheel;
    }
    else {
      resolved.target_wheel = 0
    }

    return resolved;
    }
};

module.exports = CANTestInfo;
