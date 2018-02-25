# EE569 :Homework Assignment #4
# Date  : April 23, 2017
# Name  : Madhvi Kannan
# USC ID: 2159965290
# email : mkannan@usc.edu

from __future__ import division, print_function, absolute_import

import tflearn
from tflearn.data_utils import shuffle, to_categorical
from tflearn.layers.core import input_data, dropout, fully_connected
from tflearn.layers.conv import conv_2d, max_pool_2d
from tflearn.layers.estimator import regression
from tflearn.data_preprocessing import ImagePreprocessing
from tflearn.data_augmentation import ImageAugmentation
import scipy
import tensorflow as tf
# Data loading and preprocessing
import cifar10
cifar10.data_path="data/CIFAR-10/"
X, Y, labels_train=cifar10.load_training_data()
X_test, Y_test,labels_test = cifar10.load_test_data()
#(X, Y), (X_test, Y_test) = cifar10.load_data()
X, Y = shuffle(X, Y)
Y = to_categorical(Y, 10)
Y_test = to_categorical(Y_test, 10)

# Real-time data preprocessing
img_prep = ImagePreprocessing()
img_prep.add_featurewise_zero_center()
img_prep.add_featurewise_stdnorm()

# Real-time data augmentation
img_aug = ImageAugmentation()
img_aug.add_random_flip_leftright()
img_aug.add_random_rotation(max_angle=25.)

# Convolutional network building
weights=tflearn.initializations.normal (shape=None, mean=0.0, stddev=0.02, dtype=tf.float32, seed=None)
network = input_data(shape=[None, 32, 32, 3],
                     data_preprocessing=img_prep)
network = conv_2d(network, 6, 5,strides=1,bias=True, activation='relu', weights_init=weights)
network = max_pool_2d(network, 2)
network = conv_2d(network, 16, 5,strides=1,bias=True, activation='relu', weights_init=weights)
network = max_pool_2d(network, 2)
network = fully_connected(network, 120, activation='relu')
network = dropout(network, 0.5)
network = fully_connected(network, 80, activation='relu')
network = dropout(network, 0.5)
network = fully_connected(network, 10, activation='softmax')
network = regression(network, optimizer='adam',
                     loss='categorical_crossentropy',
                     learning_rate=0.001)

# Train using classifier
model = tflearn.DNN(network, tensorboard_verbose=0)
model.fit(X, Y, n_epoch=25, shuffle=True, validation_set=(X_test, Y_test),
show_metric=True, batch_size=256, run_id='cifar10_cnn')
