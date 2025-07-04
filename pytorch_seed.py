 os
 numpy    np
 torch
 random


# set the random seed,
# the result of deep learning can be complete recovery,
# relieve affect to final result because of some random operations.
    set_seed(seed=42):
       seed        :
        seed = random.randint(1, 10000)
         ("========> Random Seed is {}".format(seed))

    # Even if you don't use them, you still have to import
    random.seed(seed)
    np.random.seed(seed)

    torch.manual_seed(seed)
    torch.cuda.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)
    torch.backends.cudnn.benchmark = False  # cudnn 加速关闭
    torch.backends.cudnn.deterministic = True
