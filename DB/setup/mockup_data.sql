-- Sample data for Locations
INSERT INTO Locations (LocationName, Country, City, Address, PostalCode, Latitude, Longitude)
VALUES
    ('Location 1', 'Country 1', 'City 1', 'Address 1', '12345', 12.34567890, 123.45678901),
    ('Location 2', 'Country 2', 'City 2', 'Address 2', '23456', 23.45678901, 234.56789012),
    ('Location 3', 'Country 3', 'City 3', 'Address 3', '34567', 34.56789012, 345.67890123),
    ('Location 4', 'Country 4', 'City 4', 'Address 4', '45678', 45.67890123, 456.78901234),
    ('Location 5', 'Country 5', 'City 5', 'Address 5', '56789', 56.78901234, 567.89012345);

-- Sample data for Hotels
INSERT INTO Hotels (HotelName, LocationID, StarRating, Description, ContactNumber, Email, Website, CheckInTime, CheckOutTime)
VALUES
    ('Hotel 1', 1, 4.0, 'Description for Hotel 1', '123-456-7890', 'hotel1@example.com', 'http://www.hotel1.com', '15:00:00', '11:00:00'),
    ('Hotel 2', 2, 4.5, 'Description for Hotel 2', '234-567-8901', 'hotel2@example.com', 'http://www.hotel2.com', '14:00:00', '10:00:00'),
    ('Hotel 3', 3, 3.5, 'Description for Hotel 3', '345-678-9012', 'hotel3@example.com', 'http://www.hotel3.com', '14:30:00', '10:30:00'),
    ('Hotel 4', 4, 5.0, 'Description for Hotel 4', '456-789-0123', 'hotel4@example.com', 'http://www.hotel4.com', '15:30:00', '11:30:00'),
    ('Hotel 5', 5, 4.0, 'Description for Hotel 5', '567-890-1234', 'hotel5@example.com', 'http://www.hotel5.com', '15:00:00', '11:00:00');

-- Sample data for Rooms
INSERT INTO Rooms (HotelID, RoomNumber, RoomType, BedType, MaxOccupancy, Price, IsBooked, Description)
VALUES
    (1, 101, 'Single', 'Queen', 1, 100.00, 0, 'Single room with a queen-size bed'),
    (1, 102, 'Double', 'King', 2, 150.00, 0, 'Double room with a king-size bed'),
    (2, 201, 'Single', 'Twin', 1, 110.00, 0, 'Single room with twin beds'),
    (2, 202, 'Double', 'Queen', 2, 160.00, 0, 'Double room with a queen-size bed'),
    (3, 301, 'Single', 'Twin', 1, 120.00, 0, 'Single room with twin beds');

-- Sample data for RoomImages
INSERT INTO RoomImages (RoomID, ImageURL)
VALUES
    (1, 'http://example.com/image1.jpg'),
    (1, 'http://example.com/image2.jpg'),
    (2, 'http://example.com/image3.jpg'),
    (3, 'http://example.com/image4.jpg'),
    (4, 'http://example.com/image5.jpg');

-- Sample data for Amenities
INSERT INTO Amenities (AmenityName, Description, Category, Cost, IsChargeable)
VALUES
    ('Pool', 'Outdoor swimming pool', 'Recreation', 10.00, 1),
    ('Gym', 'Fully equipped fitness center', 'Recreation', 5.00, 1),
    ('Wi-Fi', 'Free Wi-Fi access', 'Internet', 0.00, 0),
    ('Parking', 'On-site parking', 'Parking', 15.00, 1),
    ('Restaurant', 'On-site restaurant', 'Dining', 0.00, 0);

-- Sample data for HotelAmenities
INSERT INTO HotelAmenities (HotelID, AmenityID)
VALUES
    (1, 1),
    (1, 2),
    (2, 3),
    (3, 4),
    (4, 5);

-- Sample data for Customers
INSERT INTO Customers (FirstName, LastName, Email, Phone, Address, DateOfBirth)
VALUES
    ('John', 'Doe', 'john@example.com', '123-456-7890', '123 Main St', '1980-05-15'),
    ('Alice', 'Smith', 'alice@example.com', '234-567-8901', '456 Elm St', '1992-12-02'),
    ('Bob', 'Johnson', 'bob@example.com', '345-678-9012', '789 Oak St', '1975-08-21'),
    ('Eve', 'Williams', 'eve@example.com', '456-789-0123', '101 Pine St', '1988-03-10'),
    ('Charlie', 'Davis', 'charlie@example.com', '567-890-1234', '202 Cedar St', '1995-10-30');

-- Sample data for Reservations
INSERT INTO Reservations (CustomerID, CheckInDate, CheckOutDate, TotalAmount, ReservationDate)
VALUES
    (1, '2023-11-15', '2023-11-20', 450.00, '2023-11-01'),
    (2, '2023-12-05', '2023-12-10', 600.00, '2023-11-20'),
    (3, '2023-11-25', '2023-11-30', 525.00, '2023-11-15'),
    (4, '2023-12-20', '2023-12-25', 750.00, '2023-12-05'),
    (5, '2023-12-10', '2023-12-15', 500.00, '2023-12-01');

-- Sample data for RoomReservations
INSERT INTO RoomReservations (ReservationID, RoomID)
VALUES
    (1, 1),
    (1, 2),
    (2, 3),
    (2, 4),
    (3, 5);

-- Sample data for Payments
INSERT INTO Payments (ReservationID, PaymentDate, Amount, PaymentMethod)
VALUES
    (1, '2023-11-05', 450.00, 'Credit Card'),
    (2, '2023-11-25', 600.00, 'Credit Card'),
    (3, '2023-11-20', 525.00, 'PayPal'),
    (4, '2023-12-10', 750.00, 'Credit Card'),
    (5, '2023-12-05', 500.00, 'PayPal');

-- Sample data for Reviews
INSERT INTO Reviews (HotelID, CustomerID, Rating, Comment, ReviewDate)
VALUES
    (1, 1, 4, 'Great stay!', '2023-11-18'),
    (1, 2, 5, 'Excellent hotel!', '2023-11-21'),
    (2, 3, 3, 'Average experience', '2023-12-07'),
    (2, 4, 5, 'Loved it!', '2023-12-15'),
    (3, 5, 4, 'Good service', '2023-12-10');

-- Sample data for RoomReviews
INSERT INTO RoomReviews (ReviewID, RoomID)
VALUES
    (1, 1),
    (2, 2),
    (3, 3),
    (4, 4),
    (5, 5);

-- Sample data for Promotions
INSERT INTO Promotions (HotelID, PromotionName, Description, DiscountPercentage, StartDate, EndDate, IsCouponCodeRequired, CouponCode)
VALUES
    (1, 'Holiday Special', 'Get 15% off during the holiday season', 15.00, '2023-11-15', '2023-12-31', 1, 'HOLIDAY15'),
    (2, 'Weekend Getaway', 'Book for the weekend and save 10%', 10.00, '2023-12-01', '2023-12-15', 0, NULL),
    (3, 'Early Bird Offer', 'Book in advance and enjoy a 20% discount', 20.00, '2023-11-10', '2023-12-31', 1, 'EARLYBIRD20'),
    (4, 'Last Minute Deal', 'Last-minute booking at discounted rates', 15.00, '2023-12-15', '2023-12-31', 1, 'LASTMINUTE15'),
    (5, 'Family Special', 'Discounts for families', 12.00, '2023-11-20', '2023-12-31', 1, 'FAMILY12');

-- Sample data for Employees
INSERT INTO Employees (FirstName, LastName, Email, Phone, Position, HotelID)
VALUES
    ('Michael', 'Johnson', 'michael@example.com', '123-456-7890', 'Manager', 1),
    ('Sarah', 'Anderson', 'sarah@example.com', '234-567-8901', 'Front Desk Clerk', 1),
    ('David', 'Lee', 'david@example.com', '345-678-9012', 'Housekeeping', 1),
    ('Emily', 'Smith', 'emily@example.com', '456-789-0123', 'Chef', 2),
    ('Alex', 'Brown', 'alex@example.com', '567-890-1234', 'Concierge', 2);

-- Sample data for Events
INSERT INTO Events (HotelID, EventName, Description, EventDate, StartTime, EndTime, MaxCapacity, RegistrationURL)
VALUES
    (1, 'Conference 2023', 'Annual conference event', '2023-11-25', '09:00:00', '17:00:00', 150, 'http://example.com/conference'),
    (2, 'Music Night', 'Live music performance', '2023-12-05', '20:00:00', '23:00:00', 100, 'http://example.com/music-night'),
    (3, 'Workshop', 'Educational workshop', '2023-11-30', '10:00:00', '15:00:00', 50, 'http://example.com/workshop'),
    (4, 'New Year''s Eve Party', 'Celebrate the New Year', '2023-12-31', '21:00:00', '02:00:00', 200, 'http://example.com/new-year-party'),
    (5, 'Family Fun Day', 'Fun activities for the whole family', '2023-12-10', '12:00:00', '16:00:00', 80, 'http://example.com/family-fun-day');
