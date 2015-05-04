-- phpMyAdmin SQL Dump
-- version 4.2.7.1
-- http://www.phpmyadmin.net
--
-- Host: localhost
-- Generation Time: Apr 05, 2015 at 11:24 
-- Server version: 5.6.20
-- PHP Version: 5.5.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;

--
-- Database: `elmoseram`
--

-- --------------------------------------------------------

--
-- Table structure for table `t_messages`
--

CREATE TABLE IF NOT EXISTS `t_messages` (
`id` bigint(20) NOT NULL,
  `src` bigint(20) NOT NULL,
  `dst` bigint(20) NOT NULL,
  `date` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `body` varchar(4096) COLLATE utf8_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='messages of users' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

-- --------------------------------------------------------

--
-- Table structure for table `t_friends`
--

CREATE TABLE IF NOT EXISTS `t_friends` (
`id` bigint(20) NOT NULL,
  `user` bigint(20) NOT NULL,
  `friend` bigint(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_bin COMMENT='friends' AUTO_INCREMENT=1 ;

-- --------------------------------------------------------

--
-- Table structure for table `t_users`
--

CREATE TABLE IF NOT EXISTS `t_users` (
  `username` bigint(20) NOT NULL,
  `password` binary(16) NOT NULL,
  `scrname` varchar(32) CHARACTER SET utf8 COLLATE utf8_bin NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf16 COLLATE=utf16_bin COMMENT='username and password of users';

--
-- Dumping data for table `t_users`
--

--
-- Indexes for dumped tables
--

--
-- Indexes for table `t_messages`
--
ALTER TABLE `t_messages`
 ADD PRIMARY KEY (`id`);

--
-- Indexes for table `t_users`
--
ALTER TABLE `t_users`
 ADD PRIMARY KEY (`username`);

--
-- Indexes for table `t_friends`
--
ALTER TABLE `t_friends`
 ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `t_messages`
--
ALTER TABLE `t_messages`
MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;

-- AUTO_INCREMENT for table `t_friends`
--
ALTER TABLE `t_friends`
MODIFY `id` bigint(20) NOT NULL AUTO_INCREMENT;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
