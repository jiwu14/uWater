-- uWater DB Schema

create table Users(
  id int primary key auto_increment,
  username varchar(100) UNIQUE NOT NULL,
  hash varchar(255) NOT NULL
);

create table UserSetting(
  userId int primary key,
  minMoisture float DEFAULT 0.01,
  timeOfDayToWater time DEFAULT '06:00:00',
  minPrecipitationChance float DEFAULT 0.25,
  maxTimeToRain int DEFAULT 480,
  lat float,
  lon float,
  CONSTRAINT USU_FK FOREIGN KEY (userId) REFERENCES Users(id)
);

create table WaterTimeRanges(
  userId int,
  startTime time,
  endTime time NOT NULL,
  PRIMARY KEY(userId, startTime),
  UNIQUE(userId, endTime),
  CONSTRAINT WTRU_FK FOREIGN KEY (userId) REFERENCES Users(id)
);

create table DeviceData(
  id int primary key auto_increment,
  userId int NOT NULL,
  timestamp datetime,
  humidity float,
  relay int,
  CONSTRAINT DDU_FK FOREIGN KEY (userId) REFERENCES Users(id)
);

create table WeatherData(
  id int primary key auto_increment,
  userId int NOT NULL,
  timestamp datetime,
  precipProbability float,
  CONSTRAINT WDU_FK FOREIGN KEY (userId) REFERENCES Users(id)
);

