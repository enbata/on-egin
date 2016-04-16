-- MySQL Administrator dump 1.4
--
-- ------------------------------------------------------
-- Server version	5.0.45-Debian_1ubuntu3.3-log


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;


--
-- Create schema elkarte_gastronomikoa
--

CREATE DATABASE IF NOT EXISTS elkarte_gastronomikoa;
USE elkarte_gastronomikoa;

--
-- Definition of table `elkarte_gastronomikoa`.`Aukerak`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Aukerak`;
CREATE TABLE  `elkarte_gastronomikoa`.`Aukerak` (
  `Aizenaeus` varchar(20) default NULL,
  `Aizenagazt` varchar(20) default NULL,
  `AKodea` int(11) default NULL,
  `AOrdena` int(11) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Aukerak`
--

/*!40000 ALTER TABLE `Aukerak` DISABLE KEYS */;
LOCK TABLES `Aukerak` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Aukerak` VALUES  ('Edariak','',1,1),
 ('Freskagarriak','',2,2),
 ('Kontserbak','',3,3),
 ('Bestelakoak','',4,4);
UNLOCK TABLES;
/*!40000 ALTER TABLE `Aukerak` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Bazkideak`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Bazkideak`;
CREATE TABLE  `elkarte_gastronomikoa`.`Bazkideak` (
  `Izena` varchar(20) default NULL,
  `Zenbakia1` int(11) default NULL,
  `Zenbakia2` int(11) default NULL,
  `Abizena1` varchar(20) default NULL,
  `Abizena2` varchar(20) default NULL,
  `Helbidea` varchar(30) default NULL,
  `Tel1` varchar(10) default NULL,
  `Tel2` varchar(10) default NULL,
  `PK` varchar(10) default NULL,
  `Herria` varchar(20) default NULL,
  `Jubilatua` tinyint(1) default NULL,
  `JData` date default NULL,
  `NA` varchar(20) default NULL,
  `Kontua` varchar(50) default NULL,
  `Emaila` varchar(30) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Bazkideak`
--

/*!40000 ALTER TABLE `Bazkideak` DISABLE KEYS */;
LOCK TABLES `Bazkideak` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Bazkideak` VALUES  ('Manex',1,2,'Agirre','Onandia','Araba Kalea 24 4-E','943021503','606826543','20800','Zarautz',0,'1984-10-03','44333112','1234','jaimejasmi@gmail.com');
UNLOCK TABLES;
/*!40000 ALTER TABLE `Bazkideak` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Bodega`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Bodega`;
CREATE TABLE  `elkarte_gastronomikoa`.`Bodega` (
  `Gaikodea` int(11) default NULL,
  `Gaikopurua` int(11) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Bodega`
--

/*!40000 ALTER TABLE `Bodega` DISABLE KEYS */;
LOCK TABLES `Bodega` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Bodega` VALUES  (1,6),
 (2,2),
 (3,29),
 (4,9),
 (5,5),
 (6,10),
 (7,20),
 (8,75),
 (9,70),
 (10,350),
 (11,200),
 (12,7),
 (13,45),
 (14,5);
UNLOCK TABLES;
/*!40000 ALTER TABLE `Bodega` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Elkartea`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Elkartea`;
CREATE TABLE  `elkarte_gastronomikoa`.`Elkartea` (
  `Gaikodea` int(11) default NULL,
  `Kopurua` int(11) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Elkartea`
--

/*!40000 ALTER TABLE `Elkartea` DISABLE KEYS */;
LOCK TABLES `Elkartea` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Elkartea` VALUES  (2,5),
 (5,7),
 (3,32),
 (4,10),
 (1,14),
 (10,50),
 (11,295),
 (14,5),
 (7,30),
 (6,20),
 (9,45),
 (13,5),
 (12,3),
 (8,75);
UNLOCK TABLES;
/*!40000 ALTER TABLE `Elkartea` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`ElkarteaPrint`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`ElkarteaPrint`;
CREATE TABLE  `elkarte_gastronomikoa`.`ElkarteaPrint` (
  `GOrdena` int(11) default NULL,
  `AOrdena` int(11) default NULL,
  `GIzenaeus` varchar(20) default NULL,
  `AIzenaeus` varchar(20) default NULL,
  `Kopurua` double default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`ElkarteaPrint`
--

/*!40000 ALTER TABLE `ElkarteaPrint` DISABLE KEYS */;
LOCK TABLES `ElkarteaPrint` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `ElkarteaPrint` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`ElkartekoDatuak`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`ElkartekoDatuak`;
CREATE TABLE  `elkarte_gastronomikoa`.`ElkartekoDatuak` (
  `EIzena` varchar(20) default NULL,
  `EHelbidea` varchar(30) default NULL,
  `EPK` varchar(10) default NULL,
  `EHerria` varchar(20) default NULL,
  `ETel` varchar(10) default NULL,
  `Epasahitza` varchar(10) default NULL,
  `Faltak` tinyint(1) default NULL,
  `Kontua` varchar(30) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`ElkartekoDatuak`
--

/*!40000 ALTER TABLE `ElkartekoDatuak` DISABLE KEYS */;
LOCK TABLES `ElkartekoDatuak` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`ElkartekoDatuak` VALUES  ('Arrano kultur elkart','Musika Plaza','20800','Zarautz','','2007',1,'');
UNLOCK TABLES;
/*!40000 ALTER TABLE `ElkartekoDatuak` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Erosketak`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Erosketak`;
CREATE TABLE  `elkarte_gastronomikoa`.`Erosketak` (
  `ErosketaKodea` int(11) NOT NULL auto_increment,
  `GaiKodea` int(11) default NULL,
  `GaiKopurua` int(11) default NULL,
  `Data` date default NULL,
  `HorniKodea` int(11) default NULL,
  `ErosketaPrezioa` varchar(20) default NULL,
  PRIMARY KEY  (`ErosketaKodea`)
) ENGINE=MyISAM AUTO_INCREMENT=15 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Erosketak`
--

/*!40000 ALTER TABLE `Erosketak` DISABLE KEYS */;
LOCK TABLES `Erosketak` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Erosketak` VALUES  (1,1,24,'2008-03-27',1,'1,23'),
 (2,2,12,'2008-03-27',1,'2,4'),
 (3,3,89,'2008-03-27',1,'1'),
 (4,4,21,'2008-03-27',2,'0,56'),
 (5,5,12,'2008-03-27',1,'1,2'),
 (6,6,30,'2008-04-01',1,'0,4'),
 (7,7,50,'2008-04-01',1,'0,4'),
 (8,8,150,'2008-04-01',1,'0,5'),
 (9,9,120,'2008-04-01',1,'0,90'),
 (10,10,400,'2008-04-01',1,'0,20'),
 (11,11,500,'2008-04-01',1,'0,30'),
 (12,12,10,'2008-04-01',1,'2,50'),
 (13,13,50,'2008-04-01',1,'0,20'),
 (14,14,10,'2008-04-01',1,'1,25');
UNLOCK TABLES;
/*!40000 ALTER TABLE `Erosketak` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Erregistroa`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Erregistroa`;
CREATE TABLE  `elkarte_gastronomikoa`.`Erregistroa` (
  `Errkodea` int(11) NOT NULL auto_increment,
  `Eguna` date default NULL,
  `Ordua` datetime default NULL,
  PRIMARY KEY  (`Errkodea`)
) ENGINE=MyISAM AUTO_INCREMENT=7 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Erregistroa`
--

/*!40000 ALTER TABLE `Erregistroa` DISABLE KEYS */;
LOCK TABLES `Erregistroa` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Erregistroa` VALUES  (1,'2008-03-27','0000-00-00 00:00:00'),
 (2,'2008-03-27','0000-00-00 00:00:00'),
 (3,'2008-04-01','0000-00-00 00:00:00'),
 (4,'2008-04-01','0000-00-00 00:00:00'),
 (5,'2008-04-28','0000-00-00 00:00:00'),
 (6,'2008-04-29','0000-00-00 00:00:00');
UNLOCK TABLES;
/*!40000 ALTER TABLE `Erregistroa` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`FaltaPrint`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`FaltaPrint`;
CREATE TABLE  `elkarte_gastronomikoa`.`FaltaPrint` (
  `Eguna` datetime default NULL,
  `Aukera` varchar(20) default NULL,
  `Gaia` varchar(20) default NULL,
  `Kopurua` int(11) default NULL,
  `Prezioa` varchar(20) default NULL,
  `Zenbat` int(11) default NULL,
  `Elkartea` varchar(20) default NULL,
  `Bazkidea` varchar(20) default NULL,
  `Ordainketa` varchar(10) default NULL,
  `BazkideKodea` int(11) default NULL,
  `AOrdena` int(11) default NULL,
  `GOrdena` int(11) default NULL,
  `Kultura` double default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`FaltaPrint`
--

/*!40000 ALTER TABLE `FaltaPrint` DISABLE KEYS */;
LOCK TABLES `FaltaPrint` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `FaltaPrint` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Faltak`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Faltak`;
CREATE TABLE  `elkarte_gastronomikoa`.`Faltak` (
  `FKodea` int(11) NOT NULL auto_increment,
  `GKodea` int(11) default NULL,
  `GKopurua` int(11) default NULL,
  `DAurrekoa` date default NULL,
  `DAzkena` date default NULL,
  PRIMARY KEY  (`FKodea`)
) ENGINE=MyISAM AUTO_INCREMENT=8 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Faltak`
--

/*!40000 ALTER TABLE `Faltak` DISABLE KEYS */;
LOCK TABLES `Faltak` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Faltak` VALUES  (6,3,-1,'2008-04-01','2008-04-28'),
 (3,2,-5,'2008-03-27','2008-04-01'),
 (4,9,-5,'2008-04-01','2008-04-01'),
 (5,1,-4,'2008-04-01','2008-04-01'),
 (7,3,-2,'2008-04-28','2008-04-29');
UNLOCK TABLES;
/*!40000 ALTER TABLE `Faltak` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Gaiak`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Gaiak`;
CREATE TABLE  `elkarte_gastronomikoa`.`Gaiak` (
  `Gizenaeus` varchar(20) default NULL,
  `Materiala` tinyint(1) default NULL,
  `Gprezioa` varchar(20) default NULL,
  `Menpekotasuna` int(11) default NULL,
  `GKodea` int(11) default NULL,
  `AKodea` int(11) default NULL,
  `Gizenagaz` varchar(20) default NULL,
  `GOrdena` int(11) default NULL,
  `erabilgarri` tinyint(4) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Gaiak`
--

/*!40000 ALTER TABLE `Gaiak` DISABLE KEYS */;
LOCK TABLES `Gaiak` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Gaiak` VALUES  ('Sagardoa',1,'2,75',0,1,1,'',1,1),
 ('Eskilarapeko ardoa',1,'1,25',0,2,1,'',2,1),
 ('Txakolina',1,'5,25',0,3,1,'',5,1),
 ('Ardo berezia',1,'4,5',0,4,1,'',3,1),
 ('Rueda',1,'2,56',0,5,1,'',4,1),
 ('Kas limoiduna',1,'0,75',0,6,2,'',1,1),
 ('Coca Cola',1,'0,75',0,7,2,'',2,1),
 ('San Miguel',1,'0,75',0,8,2,'',3,1),
 ('Laiker',1,'1,30',0,9,2,'',4,1),
 ('Ilarrak',1,'0,30',0,10,3,'',1,1),
 ('Kafe eta infusioak',1,'0,40',2,11,4,'',1,1),
 ('Oliba olio botila ha',1,'5',0,12,4,'',2,1),
 ('Oliba botila txikia',1,'0,40',0,13,4,'',3,1),
 ('Ekilore olioa',1,'2,5',0,14,4,'',4,1);
UNLOCK TABLES;
/*!40000 ALTER TABLE `Gaiak` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Hornitzaileak`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Hornitzaileak`;
CREATE TABLE  `elkarte_gastronomikoa`.`Hornitzaileak` (
  `HGakoa` int(11) NOT NULL auto_increment,
  `HIzena` varchar(20) default NULL,
  `HHelbidea` varchar(20) default NULL,
  `HTel` varchar(10) default NULL,
  `HPK` varchar(10) default NULL,
  `HHerria` varchar(20) default NULL,
  PRIMARY KEY  (`HGakoa`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Hornitzaileak`
--

/*!40000 ALTER TABLE `Hornitzaileak` DISABLE KEYS */;
LOCK TABLES `Hornitzaileak` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Hornitzaileak` VALUES  (1,'Honiter S.L','Euskadi etorbidea','11460320','9755232','Andoain'),
 (2,'asd','asd','879','89','asd');
UNLOCK TABLES;
/*!40000 ALTER TABLE `Hornitzaileak` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`KontuaPrint`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`KontuaPrint`;
CREATE TABLE  `elkarte_gastronomikoa`.`KontuaPrint` (
  `Eguna` date default NULL,
  `Aukera` varchar(20) default NULL,
  `Gaia` varchar(20) default NULL,
  `Kopurua` int(11) default NULL,
  `Prezioa` varchar(20) default NULL,
  `Zenbat` int(11) default NULL,
  `Elkartea` varchar(20) default NULL,
  `Bazkidea` varchar(20) default NULL,
  `Ordainketa` varchar(20) default NULL,
  `BazkideKodea` int(11) default NULL,
  `AOrdena` int(11) default NULL,
  `GOrdena` int(11) default NULL,
  `kultura` double default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`KontuaPrint`
--

/*!40000 ALTER TABLE `KontuaPrint` DISABLE KEYS */;
LOCK TABLES `KontuaPrint` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `KontuaPrint` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Kontuak`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Kontuak`;
CREATE TABLE  `elkarte_gastronomikoa`.`Kontuak` (
  `KKodea` int(11) default NULL,
  `BKodea` int(11) default NULL,
  `GKodea` int(11) default NULL,
  `AKodea` int(11) default NULL,
  `GKopurua` int(11) default NULL,
  `Data` date default NULL,
  `KMota` varchar(20) default NULL,
  `OMota` varchar(20) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Kontuak`
--

/*!40000 ALTER TABLE `Kontuak` DISABLE KEYS */;
LOCK TABLES `Kontuak` WRITE;
INSERT INTO `elkarte_gastronomikoa`.`Kontuak` VALUES  (0,0,3,1,5,'2008-03-27','FALTAO',NULL),
 (1,0,3,1,12,'2008-03-27','FALTAO',NULL),
 (2,0,3,1,1,'2008-03-27','FALTAA',NULL),
 (3,0,3,1,1,'2008-04-01','FALTAA',NULL),
 (4,1,4,1,2,'2008-04-29','KONTUA','Dirua jarrita'),
 (4,1,3,1,5,'2008-04-29','KONTUA','Dirua jarrita'),
 (4,1,11,4,5,'2008-04-29','KONTUA','Dirua jarrita'),
 (5,1,3,1,1,'2008-04-29','FALTAO',NULL);
UNLOCK TABLES;
/*!40000 ALTER TABLE `Kontuak` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`Kultura`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`Kultura`;
CREATE TABLE  `elkarte_gastronomikoa`.`Kultura` (
  `KKodea` int(11) default NULL,
  `BKodea` int(11) default NULL,
  `KKopurua` double default NULL,
  `Data` date default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`Kultura`
--

/*!40000 ALTER TABLE `Kultura` DISABLE KEYS */;
LOCK TABLES `Kultura` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `Kultura` ENABLE KEYS */;


--
-- Definition of table `elkarte_gastronomikoa`.`OsoaPrint`
--

DROP TABLE IF EXISTS `elkarte_gastronomikoa`.`OsoaPrint`;
CREATE TABLE  `elkarte_gastronomikoa`.`OsoaPrint` (
  `Eguna` int(11) default NULL,
  `Gastua` varchar(10) default NULL,
  `Zenbatekoa` double default NULL,
  `Bazkidea` varchar(20) default NULL,
  `BazkideKodea` int(11) default NULL,
  `Zenbat` int(11) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Dumping data for table `elkarte_gastronomikoa`.`OsoaPrint`
--

/*!40000 ALTER TABLE `OsoaPrint` DISABLE KEYS */;
LOCK TABLES `OsoaPrint` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `OsoaPrint` ENABLE KEYS */;




/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
