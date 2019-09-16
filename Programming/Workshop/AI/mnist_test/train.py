# -*- coding: utf-8 -*-
# @Time    : 2018/10/1 0001 22:51
# @Author  : J.K LuMinzhe
# @Site    : 
# @File    : train.py
# @Software: PyCharm

import os
import sys
import math
import time
import numpy as np
import tensorflow as tf
from tensorflow.contrib import slim
from tensorflow import app
# from tensorflow.contrib.learn.python.learn.datasets.mnist import dense_to_one_hot

import mnist_util
import mnist_params

import log_util

def dense_to_one_hot(labels_dense, num_classes):
  """Convert class labels from scalars to one-hot vectors."""
  num_labels = labels_dense.shape[0]
  index_offset = np.arange(num_labels) * num_classes
  labels_one_hot = np.zeros((num_labels, num_classes))
  labels_one_hot.flat[index_offset + labels_dense.ravel()] = 1
  return labels_one_hot

def train(epoch_num=200, batch_size=20):
  images, labels = mnist_util.load_mnist(mnist_params.MNIST_DATASET_PATH, 'train')
  images = np.reshape(images, (-1, 28, 28, 1)).astype(np.float32)
  labels = dense_to_one_hot(labels, mnist_params.MNIST_NUM_CLASSES).astype(np.float32)
  
  watch = log_util.Watch('TrainInfo')
  with tf.Session() as sess:
    with tf.variable_scope('mnist'), \
         slim.arg_scope([slim.conv2d, slim.fully_connected],
                        weights_initializer=tf.truncated_normal_initializer(stddev=0.01),
                        biases_initializer=tf.zeros_initializer(),
                        activation_fn=tf.nn.relu,
                        trainable=True):
      global_step = tf.Variable(0, name='global_step', trainable=False)
      
      image_batch = tf.placeholder(tf.float32, shape=(None, 28, 28, 1), name='image')
      net = slim.conv2d(image_batch, 4, kernel_size=[3,3], stride=1, padding='SAME', trainable=True)
      net = slim.max_pool2d(net, kernel_size=[2,2], stride=2)
      net = slim.flatten(net)
      fc = slim.fully_connected(net, 32, trainable=True)
      # fc = slim.flatten(image_batch)
      logits = slim.fully_connected(fc, 10, trainable=True)
      
      label_batch = tf.placeholder(tf.float32, shape=(None, mnist_params.MNIST_NUM_CLASSES), name='label')
      cross_entropy = tf.nn.sigmoid_cross_entropy_with_logits(logits=logits, labels=label_batch)
      predict = slim.softmax(cross_entropy)
      loss = tf.reduce_mean(cross_entropy)
      optimizer = tf.train.AdamOptimizer(learning_rate=0.1, epsilon=1.0e-08, name='adam')
      optimizer.minimize(loss, global_step=global_step, name='train_op')
    sess.run(tf.global_variables_initializer())
    saver = tf.train.Saver()
    # coord = tf.train.Coordinator()
    # threads = tf.train.start_queue_runners(sess, coord)
    train_op = sess.graph.get_operation_by_name('mnist/train_op')
    for i in range(200):
      for j in range(len(images) // batch_size):
        try:
          input_image = images[batch_size * j : batch_size * (j + 1)]
          input_label = labels[batch_size * j : batch_size * (j + 1)]
          [r_step, r_loss, _] = sess.run([global_step, loss, train_op],
                                                 feed_dict={image_batch: input_image, label_batch: input_label})
          watch.display('step %d, loss is %.3f' % (r_step, r_loss))
          # watch.display('step %d, loss is %.3f, label is %s, image is %s'
          #               % (r_step, r_loss, str(input_label.argmax(axis=1)), str(input_image[:, 14, 14, 0])))
        except tf.errors.OutOfRangeError:
          saver.save(sess, mnist_params.MNIST_MODEL)
          print('done training mnist')
          break
    # coord.request_stop()
    # coord.join(threads)


def main(_):
  train()


if __name__ == '__main__':
  app.run()
