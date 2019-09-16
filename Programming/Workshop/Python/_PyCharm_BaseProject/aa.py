import tensorflow as tf
import os
# 首先，创建一个TensorFlow常量=>2
const = tf.constant(2.0, name='const')

# 创建TensorFlow变量b和c
b = tf.Variable(2.0, name='b')
c = tf.Variable(1.0, dtype=tf.float32, name='c')

# 创建operation
d = tf.add(b, c, name='d')
e = tf.add(c, const, name='e')
a = tf.multiply(d, e, name='a')

# 定义init operation
init_op = tf.global_variables_initializer()

# session
with tf.Session() as sess:
	# 2. 运行init operation
	sess.run(init_op)
	# 计算
	status=os.fork()
	assert status!=-1,"Fork Error!"
	if status==0:
		d_out = sess.run(d)
		print("Variable d is {}".format(d_out))
	else:
		os.wait()
		a_out = sess.run(a)
		print("Variable a is {}".format(a_out))

