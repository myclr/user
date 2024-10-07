const express = require('express');
const five = require('johnny-five');
const { PCA9685 } = require('johnny-five/lib/pca9685'); // Import PCA9685 driver
const app = express();
const port = 3000;

let servo;

// Initialize the PCA9685
const board = new five.Board();

board.on('ready', () => {
    // Initialize PCA9685
    const pwm = new PCA9685();
    servo = new five.Servo({
        pin: 0, // Use channel 0 of the PCA9685
        pwm: pwm // Link it with the PCA9685
    });

    console.log('PCA9685 and Servo are ready');

    // Serve the frontend HTML
    app.use(express.static('public'));
    const docRef = firestore.collection('admin-login').doc('new-document-id');


    // Endpoint to control the servo
    app.get('/control-servo', (req, res) => {
        const quantity = parseInt(req.query.quantity, 10);

        if (quantity > 0) {
            // Control the servo
            for (let i = 0; i < quantity; i++) {
                servo.to(90); // Move to 90 degrees
                board.wait(2000, () => {
                    servo.to(0); // Move back to 0 degrees
                });
            }
            res.send({ message: `Servo activated ${quantity} times` });
        } else {
            res.status(400).send({ error: 'Invalid quantity' });
        }
    });

    app.listen(port, () => {
        console.log(`Server is running on http://localhost:${port}`);
    });
});
