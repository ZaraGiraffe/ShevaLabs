-- Insert a new hotel into the Hotels table
INSERT INTO Hotels (HotelName, LocationID, StarRating, Description, ContactNumber, Email, Website)
VALUES ('New Hotel', 1, 4.5, 'A great hotel', '123-456-7890', 'hotel@example.com', 'http://www.example.com');

-- Check the inserted row to see if the default CheckInTime and CheckOutTime values are set
SELECT * FROM Hotels WHERE HotelName = 'New Hotel';

-- Verify that the CheckInTime and CheckOutTime have been set to the default values
