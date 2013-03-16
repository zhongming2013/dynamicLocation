//房间坐标信息表，把一段走廊看成一个房间
create table room (
id integer primary key autoincrement,
floor integer not null,
number integer not null,
x integer not null,
y integer not null
);
//position id---------------OLD
INSERT INTO room (floor,number,x,y) VALUES (6,37,1100,80),(6,36,950,84),(6,35,810,90),(6,34,650,80),(6,33,490,80);

//员工基本信息表
CREATE TABLE employee (
id INTEGER PRIMARY KEY AUTOINCREMENT,
fixId INTEGER NOT NULL,
name VARCHAR(20) NOT NULL,
department VARCHAR(40) NOT NULL,
extension INTEGER NOT NULL,
email VARCHAR(40) NOT NULL,
startDate DATE NOT NULL
);
INSERT INTO employee (fixId,name,department,extension,email,startDate) VALUES (1,'ZhangSan','IT Dept.',234,'zhang@SIST.com',CURRENT_DATE);
INSERT INTO employee (fixId,name,department,extension,email,startDate) VALUES (2,'Lisi','HR',236,'li@SIST.com',CURRENT_DATE);
INSERT INTO employee (fixId,name,department,extension,email,startDate) VALUES (3,'Wangwu','HR',235,'wang@SIST.edu',CURRENT_DATE);

//参考节点配置信息表，包括房间号和网络地址,当前温度
CREATE TABLE referNode (
id INTEGER PRIMARY KEY AUTOINCREMENT,
netId VARCHAR(4) NOT NULL,
floor INTEGER NOT NULL,
number integer not null,
tempPeriod integer not null
);
//room number ----------------------------------------637--------636-----635------634-------633-----637zou--636zou-635zou--634zou--633zou----
INSERT INTO referNode (netId,floor,number,tempPeriod) VALUES ('0001',6,37,30),('0DEF',6,36,30),('FA11',6,35,30),('0A21',6,34,30);
SELECT R.floor,R.number,R.x,R.y FORM room R LEFT JOIN  referNode N ON R.floor=N.floor AND R.number=N.number

//移动节点定位历史记录表
create table location(
id integer primary key autoincrement,
fixId integer not null,
netId VARCHAR(4) NOT NULL,
floor integer not null,
number integer not null,
help integer not null,
time date default (datetime('now','localtime'))
);

//移动节点配置信息表
create table mobileConfig (
id integer primary key autoincrement,
fixId integer not null,
mode integer not null,
dstAddr VARCHAR(4) not null,
period integer not null,
selfAddr VARCHAR(4) not null
);
insert into mobileConfig values(1,1,0,'0000',20,'1122');

//房间温度历史记录
create table temperature (
id integer primary key autoincrement,
floor integer not null,
number integer not null,
temperature integer not null,
time date default (datetime('now','localtime'))
);

要求：

移动节点和参考节点每次更该NETID都必须的重新发送一次配置信息；