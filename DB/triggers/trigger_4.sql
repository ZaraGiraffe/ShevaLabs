DELIMITER $$

CREATE TRIGGER SetDefaultCheckInOutTimes BEFORE INSERT ON Hotels
FOR EACH ROW
BEGIN
    SET NEW.CheckInTime = '15:00:00';
    SET NEW.CheckOutTime = '11:00:00';
END $$

DELIMITER ;
