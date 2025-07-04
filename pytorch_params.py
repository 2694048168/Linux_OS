    get_params(model):
    # num_params = sum(param.numel() for param in model.parameters())
    trainable_params = sum(
        param.numel()     param    model.parameters() if param.requires_grad
    )
    print(f"The number of trainable parameters for model is: {trainable_params}")
    print(
        f"The number of trainable parameters for model is: {trainable_params/1000.0:.6f}K"
    )
    print(
        f"The number of trainable parameters for model is: {trainable_params/1000000.0:.6f}M\n"
    )

           trainable_params
