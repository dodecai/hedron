﻿module Vite.Platform.VKBuffer;

namespace Hedron {

//static inline uint32_t GetMemoryTypeIndex(const vk::PhysicalDevice &physicalDevice, uint32_t typeBits, vk::MemoryPropertyFlags properties) {
//    auto gpuMemoryProps = physicalDevice.getMemoryProperties();
//    for (uint32_t i = 0; i < gpuMemoryProps.memoryTypeCount; i++) {
//        if ((typeBits & 1) == 1) {
//            if ((gpuMemoryProps.memoryTypes[i].propertyFlags & properties) == properties) {
//                return i;
//            }
//        }
//        typeBits >>= 1;
//    }
//    return 0;
//};



//VKBuffer::VKBuffer(BufferType type, const void *data, size_t size, BufferUsage usage): Buffer(type, data, size, usage) {
    //// ToDo:: Smooth solution ... this code is ...
    //VKContext = Omnia::Application::GetContext().As<Omnia::VKContext>();
    //auto &device = VKContext->GetDevice()->Call();
    //mBuffer = DataBuffer::Copy(data, size);

    /////
    ///// Source
    ///// 
    //// Vertex Buffer...  copy index data to a buffer visible to the host (staging buffer)
    //vk::BufferCreateInfo createInfo = {};
    //createInfo.flags = vk::BufferCreateFlags();
    //createInfo.sharingMode = vk::SharingMode::eExclusive;
    //createInfo.usage = vk::BufferUsageFlagBits::eTransferSrc;
    //createInfo.size = mSize;
    //Vertices.Buffer = device.createBuffer(createInfo, nullptr);

    //vk::MemoryRequirements memoryRequirements = device.getBufferMemoryRequirements(Vertices.Buffer);
    //Vertices.Memory = device.allocateMemory(
    //    vk::MemoryAllocateInfo(
    //        memoryRequirements.size,
    //        GetMemoryTypeIndex(VKContext->GetDevice()->GetPhysicalDevice()->Call(), memoryRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent)
    //    )
    //);

    //void *destinationData = device.mapMemory(Vertices.Memory, 0, mSize, vk::MemoryMapFlags());
    //memcpy(destinationData, mBuffer.Data, mSize);
    //device.unmapMemory(Vertices.Memory);
    //device.bindBufferMemory(Vertices.Buffer, Vertices.Memory, 0);

    /////
    ///// Destination
    ///// ToDo: It was recommended to upload the data to the graphics card and keep it there due to performance. Here we leave a lot of testing for now...
    ///// Also the copy process is not included, with the current skills it is hard to decide where to place them.
    ///// 
    //// Create a device local buffer to which the (host local) vertex data will be copied and which will be used for rendering
    //vk::BufferCreateInfo createInfoT = {};
    //createInfoT.flags = vk::BufferCreateFlags();
    //createInfoT.sharingMode = vk::SharingMode::eExclusive;
    //createInfoT.usage = vk::BufferUsageFlagBits::eVertexBuffer | vk::BufferUsageFlagBits::eTransferDst;
    //createInfoT.size = mSize;
    //VerticesT.Buffer = device.createBuffer(createInfoT, nullptr);
    //memoryRequirements = device.getBufferMemoryRequirements(VerticesT.Buffer);
    //VerticesT.Memory = device.allocateMemory(
    //    vk::MemoryAllocateInfo(
    //        memoryRequirements.size,
    //        GetMemoryTypeIndex(VKContext->GetDevice()->GetPhysicalDevice()->Call(), memoryRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal)
    //    )
    //);
    //device.bindBufferMemory(VerticesT.Buffer, VerticesT.Memory, 0);
    // 
    // 
    // 
    //   ///
    ///// Source
    ///// 
    //// Index Buffer...  copy index data to a buffer visible to the host (staging buffer)
    //vk::BufferCreateInfo createInfo = {};
    //createInfo.flags = vk::BufferCreateFlags();
    //createInfo.sharingMode = vk::SharingMode::eExclusive;
    //createInfo.usage = vk::BufferUsageFlagBits::eTransferSrc; // vk::BufferUsageFlagBits::eIndexBuffer
    //createInfo.size = mSize;
    //Indices.Buffer = device.createBuffer(createInfo, nullptr);

    //vk::MemoryRequirements memoryRequirements = device.getBufferMemoryRequirements(Indices.Buffer);
    //Indices.Memory = device.allocateMemory(
    //    vk::MemoryAllocateInfo(
    //        memoryRequirements.size,
    //        GetMemoryTypeIndex(VKContext->GetDevice()->GetPhysicalDevice()->Call(), memoryRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eHostVisible | vk::MemoryPropertyFlagBits::eHostCoherent)
    //    )
    //);

    //void *destinationData = device.mapMemory(Indices.Memory, 0, mSize, vk::MemoryMapFlags());
    //memcpy(destinationData, mBuffer.Data, mSize);
    //device.unmapMemory(Indices.Memory);
    //device.bindBufferMemory(Indices.Buffer, Indices.Memory, 0);

    /////
    ///// Destination
    ///// ToDo: It was recommended to upload the data to the graphics card and keep it there due to performance. Here we leave a lot of testing for now...
    ///// Also the copy process is not included, with the current skills it is hard to decide where to place them.
    ///// 
    //// Create destination buffer with device only visibility
    //vk::BufferCreateInfo createInfoT = {};
    //createInfoT.flags = vk::BufferCreateFlags();
    //createInfoT.sharingMode = vk::SharingMode::eExclusive;
    //createInfoT.usage = vk::BufferUsageFlagBits::eIndexBuffer | vk::BufferUsageFlagBits::eTransferDst;
    //createInfoT.size = mSize;
    //IndicesT.Buffer = device.createBuffer(createInfoT, nullptr);
    //memoryRequirements = device.getBufferMemoryRequirements(IndicesT.Buffer);
    //IndicesT.Memory = device.allocateMemory(
    //    vk::MemoryAllocateInfo(
    //        memoryRequirements.size,
    //        GetMemoryTypeIndex(VKContext->GetDevice()->GetPhysicalDevice()->Call(), memoryRequirements.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal)
    //    )
    //);
    //device.bindBufferMemory(IndicesT.Buffer, IndicesT.Memory, 0);
//}

//VKBuffer::~VKBuffer() {
    //auto &device = VKContext->GetDevice()->Call();
    //// Destroy staging buffers
    //// Note: Staging buffer must not be deleted before the copies have been submitted and executed
    //device.destroyBuffer(Vertices.Buffer, nullptr);
    //device.freeMemory(Vertices.Memory, nullptr);

    //// Destroy staging buffers
    //// Note: Staging buffer must not be deleted before the copies have been submitted and executed
    //device.destroyBuffer(Indices.Buffer, nullptr);
    //device.freeMemory(Indices.Memory, nullptr);
//}

}

