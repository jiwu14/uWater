-- uWater DB Schema

create table Users(
  id int primary key auto_increment,
  username varchar(100) UNIQUE NOT NULL,
  hash varchar(255) NOT NULL
);

create table UserSetting(
  userId int primary key,
  minMoisture float DEFAULT 0.1,
  minPrecipitationChance float DEFAULT 0.25,
  maxTimeToRain int DEFAULT 480,
  lat float,
  lon float,
  CONSTRAINT USU_FK FOREIGN KEY (userId) REFERENCES Users(id)
);

create table DeviceData(
  userId int primary key,
  timestamp datetime,
  humidity float,
  relay int,
  CONSTRAINT DDU_FK FOREIGN KEY (userId) REFERENCES Users(id)
);


