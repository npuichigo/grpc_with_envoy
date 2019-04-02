# common files.
file(GLOB tmp *.cc)
set(grpc_with_envoy_SRCS ${grpc_with_envoy_SRCS} ${tmp})
# exclude executable
file (GLOB tmp main.cc grpc_test_client.cc)
exclude(grpc_with_envoy_SRCS "${grpc_with_envoy_SRCS}" ${tmp})

# Send the lists to the parent scope.
set(grpc_with_envoy_SRCS ${grpc_with_envoy_SRCS} PARENT_SCOPE)
