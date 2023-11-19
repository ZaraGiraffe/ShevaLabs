DELIMITER $$
CREATE FUNCTION CalculateEventDuration(EventID INT) RETURNS VARCHAR(10) DETERMINISTIC
BEGIN
    DECLARE EventDuration VARCHAR(10);

    SELECT CONCAT(
        HOUR(TIMEDIFF(EndTime, StartTime)), 'h ',
        MINUTE(TIMEDIFF(EndTime, StartTime)), 'm'
    ) INTO EventDuration
    FROM Events
    WHERE Events.EventID = EventID;

    RETURN EventDuration;
END;
$$
DELIMITER ;
