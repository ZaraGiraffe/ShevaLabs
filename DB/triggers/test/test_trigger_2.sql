-- Insert a new review into the Reviews table
INSERT INTO Reviews (HotelID, CustomerID, Rating, Comment, ReviewDate)
VALUES (1, 1, 4, 'Great hotel!', '2023-11-08'); -- Replace with valid values

-- Check the Hotels table to see if the StarRating column has been updated
SELECT StarRating FROM Hotels WHERE HotelID = 1; -- Replace with the actual HotelID used in the INSERT

-- Verify that the StarRating column has been updated with the new average rating
