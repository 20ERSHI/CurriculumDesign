/*
 Navicat Premium Data Transfer

 Source Server         : mysql.twentyy.cn_10140
 Source Server Type    : MySQL
 Source Server Version : 50718
 Source Host           : mysql.twentyy.cn:10140
 Source Schema         : smadata

 Target Server Type    : MySQL
 Target Server Version : 50718
 File Encoding         : 65001

 Date: 05/12/2019 02:03:50
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for product
-- ----------------------------
DROP TABLE IF EXISTS `product`;
CREATE TABLE `product`  (
  `sn` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `price` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `stock` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of product
-- ----------------------------
INSERT INTO `product` VALUES ('1', '鱼', '10', '1000');
INSERT INTO `product` VALUES ('2', '豆腐', '5', '1000');
INSERT INTO `product` VALUES ('11', 'AF钙', '3.3', '1000');
INSERT INTO `product` VALUES ('3', '青菜', '2.5', '1000');
INSERT INTO `product` VALUES ('4', '木耳', '9', '1000');
INSERT INTO `product` VALUES ('5', '西红柿', '12', '1000');
INSERT INTO `product` VALUES ('6', '白菜', '4', '1000');
INSERT INTO `product` VALUES ('7', '柠檬', '7', '999');
INSERT INTO `product` VALUES ('8', '洗衣液', '23.5', '300');
INSERT INTO `product` VALUES ('9', '肥皂', '19.1', '100');
INSERT INTO `product` VALUES ('10', '镜子', '22.33', '200');

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `userid` int(11) NOT NULL,
  `userlv` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `username` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `usertel` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  PRIMARY KEY (`userid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (1, '1', '张三', '12345678901');
INSERT INTO `user` VALUES (2, '2', '李四', '11123331122');
INSERT INTO `user` VALUES (3, '3', '王五', '12311313123');
INSERT INTO `user` VALUES (4, '4', '铁蛋', '12344411231');
INSERT INTO `user` VALUES (5, '1', '二狗', '12341151134');
INSERT INTO `user` VALUES (6, '2', '李铁牛', '17373102837');
INSERT INTO `user` VALUES (7, '3', '张三', '10974984739');
INSERT INTO `user` VALUES (8, '4', '王五', '8');
INSERT INTO `user` VALUES (9, '2', '李某', '13333333333');
INSERT INTO `user` VALUES (10, '1', '杨某', '13333333333');

-- ----------------------------
-- Table structure for vip
-- ----------------------------
DROP TABLE IF EXISTS `vip`;
CREATE TABLE `vip`  (
  `vipid` int(11) NOT NULL,
  `vipname` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT NULL,
  `vippo` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT '0.95',
  `vippoint` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci NULL DEFAULT '0',
  PRIMARY KEY (`vipid`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of vip
-- ----------------------------
INSERT INTO `vip` VALUES (1, '欧阳', '0.95', '2378.6');
INSERT INTO `vip` VALUES (2, '王五', '0.95', '2');
INSERT INTO `vip` VALUES (3, '李靖', '0.95', '5');
INSERT INTO `vip` VALUES (4, '5', '0.95', '203.75');
INSERT INTO `vip` VALUES (5, '233', '0.95', '0');

-- ----------------------------
-- Table structure for water
-- ----------------------------
DROP TABLE IF EXISTS `water`;
CREATE TABLE `water`  (
  `wid` int(11) NOT NULL COMMENT '流水号',
  `pid` int(11) NOT NULL,
  `amount` int(255) NOT NULL,
  `time` datetime(0) NOT NULL
) ENGINE = InnoDB CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of water
-- ----------------------------
INSERT INTO `water` VALUES (0, 0, 0, '2019-12-04 05:09:55');
INSERT INTO `water` VALUES (1, 2, 1, '2019-12-01 05:16:18');
INSERT INTO `water` VALUES (2, 1, 3, '2019-12-04 05:34:35');
INSERT INTO `water` VALUES (3, 1, 10, '2019-12-04 05:34:53');
INSERT INTO `water` VALUES (4, 11, 10, '2019-12-04 05:35:32');
INSERT INTO `water` VALUES (4, 2, 3, '2019-12-04 05:35:32');
INSERT INTO `water` VALUES (4, 1, 5, '2019-12-04 05:35:32');
INSERT INTO `water` VALUES (5, 11, 5, '2019-12-04 05:52:28');
INSERT INTO `water` VALUES (5, 2, 5, '2019-12-04 05:52:29');
INSERT INTO `water` VALUES (5, 1, 6, '2019-12-04 05:52:29');
INSERT INTO `water` VALUES (6, 11, 3, '2019-12-04 05:54:26');
INSERT INTO `water` VALUES (6, 2, 3, '2019-12-04 05:54:26');
INSERT INTO `water` VALUES (6, 1, 3, '2019-12-04 05:54:26');
INSERT INTO `water` VALUES (7, 11, 3, '2019-12-04 05:56:11');
INSERT INTO `water` VALUES (7, 2, 4, '2019-12-04 05:56:11');
INSERT INTO `water` VALUES (7, 1, 3, '2019-12-04 05:56:11');
INSERT INTO `water` VALUES (8, 11, 3, '2019-12-04 05:56:47');
INSERT INTO `water` VALUES (8, 2, 3, '2019-12-04 05:56:47');
INSERT INTO `water` VALUES (8, 1, 3, '2019-12-04 05:56:47');
INSERT INTO `water` VALUES (9, 11, 5, '2019-12-04 05:57:48');
INSERT INTO `water` VALUES (9, 2, 3, '2019-12-04 05:57:48');
INSERT INTO `water` VALUES (9, 1, 7, '2019-12-04 05:57:48');
INSERT INTO `water` VALUES (10, 2, 5, '2019-12-04 05:58:52');
INSERT INTO `water` VALUES (10, 1, 7, '2019-12-04 05:58:52');
INSERT INTO `water` VALUES (11, 11, 5, '2019-12-04 06:00:28');
INSERT INTO `water` VALUES (11, 2, 5, '2019-12-04 06:00:28');
INSERT INTO `water` VALUES (11, 1, 5, '2019-12-04 06:00:28');
INSERT INTO `water` VALUES (12, 11, 7, '2019-12-04 20:31:28');
INSERT INTO `water` VALUES (12, 2, 11, '2019-12-04 20:31:28');
INSERT INTO `water` VALUES (12, 1, 7, '2019-12-04 20:31:28');
INSERT INTO `water` VALUES (13, 11, 7, '2019-12-04 20:33:24');
INSERT INTO `water` VALUES (13, 2, 5, '2019-12-04 20:33:24');
INSERT INTO `water` VALUES (13, 1, 9, '2019-12-04 20:33:24');
INSERT INTO `water` VALUES (14, 11, 6, '2019-12-04 21:05:17');
INSERT INTO `water` VALUES (14, 2, 8, '2019-12-04 21:05:17');
INSERT INTO `water` VALUES (14, 1, 12, '2019-12-04 21:05:17');
INSERT INTO `water` VALUES (15, 11, 8, '2019-12-04 22:56:04');
INSERT INTO `water` VALUES (15, 2, 7, '2019-12-04 22:56:04');
INSERT INTO `water` VALUES (15, 1, 9, '2019-12-04 22:56:04');
INSERT INTO `water` VALUES (16, 10, 5, '2019-12-05 02:00:16');
INSERT INTO `water` VALUES (16, 9, 1, '2019-12-05 02:00:16');
INSERT INTO `water` VALUES (16, 8, 1, '2019-12-05 02:00:17');
INSERT INTO `water` VALUES (16, 7, 1, '2019-12-05 02:00:17');
INSERT INTO `water` VALUES (16, 6, 1, '2019-12-05 02:00:17');
INSERT INTO `water` VALUES (16, 5, 1, '2019-12-05 02:00:17');
INSERT INTO `water` VALUES (16, 4, 1, '2019-12-05 02:00:17');
INSERT INTO `water` VALUES (16, 3, 1, '2019-12-05 02:00:18');
INSERT INTO `water` VALUES (16, 2, 1, '2019-12-05 02:00:18');
INSERT INTO `water` VALUES (16, 1, 1, '2019-12-05 02:00:18');

SET FOREIGN_KEY_CHECKS = 1;
