/**
 * Created by chu on 2017/8/16 0016.
 */
var PlayerData = require("./data/player-data");

const global = {};
global.playerData = PlayerData();
module.exports = global;
export default global;